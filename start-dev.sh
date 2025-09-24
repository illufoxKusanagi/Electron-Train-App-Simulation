#!/bin/bash
set -e

echo "🚀 Starting Train App Development Environment..."

# Get project root
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "Project root: $PROJECT_ROOT"

# Function to cleanup on exit
cleanup() {
    echo "🧹 Cleaning up processes..."
    if [ ! -z "$BACKEND_PID" ]; then
        kill $BACKEND_PID 2>/dev/null || true
    fi
    if [ ! -z "$FRONTEND_PID" ]; then
        kill $FRONTEND_PID 2>/dev/null || true
    fi
    exit 0
}

# Trap cleanup on script exit
trap cleanup EXIT INT TERM

# Function to wait for backend to be ready
wait_for_backend() {
    echo "⏳ Waiting for backend to start..."
    local max_attempts=30
    local attempt=1
    
    while [ $attempt -le $max_attempts ]; do
        if curl -s http://localhost:8080/status > /dev/null 2>&1; then
            echo "✅ Backend is ready!"
            return 0
        fi
        echo "   Attempt $attempt/$max_attempts - Backend not ready yet..."
        sleep 2
        attempt=$((attempt + 1))
    done
    
    echo "❌ Backend failed to start after $max_attempts attempts"
    return 1
}

# Function to wait for frontend to be ready
wait_for_frontend() {
    echo "⏳ Waiting for frontend to start..."
    local max_attempts=15
    local attempt=1
    
    while [ $attempt -le $max_attempts ]; do
        if curl -s http://localhost:3000 > /dev/null 2>&1; then
            echo "✅ Frontend is ready!"
            return 0
        fi
        echo "   Attempt $attempt/$max_attempts - Frontend not ready yet..."
        sleep 2
        attempt=$((attempt + 1))
    done
    
    echo "❌ Frontend failed to start after $max_attempts attempts"
    return 1
}

# Start backend
echo "🔧 Starting Qt Backend..."
cd "$PROJECT_ROOT/backend"
chmod +x scripts/smart-run.sh
nohup ./scripts/smart-run.sh > backend.log 2>&1 &
BACKEND_PID=$!
echo "Backend started with PID: $BACKEND_PID"

# Wait for backend to be ready
if ! wait_for_backend; then
    echo "❌ Failed to start backend"
    exit 1
fi

# Start frontend
echo "💻 Starting Next.js Frontend..."
cd "$PROJECT_ROOT/frontend"
nohup npx next dev > ../frontend.log 2>&1 &
FRONTEND_PID=$!
echo "Frontend started with PID: $FRONTEND_PID"

# Wait for frontend to be ready
if ! wait_for_frontend; then
    echo "❌ Failed to start frontend"
    exit 1
fi

# Start Electron
echo "⚡ Starting Electron App..."
cd "$PROJECT_ROOT"
electron electron/main.js

# Keep script running until Electron closes
wait