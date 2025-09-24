#!/bin/bash
set -e

echo "🏗️  Building Qt Backend..."

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BACKEND_DIR="$(dirname "$SCRIPT_DIR")"

echo "Script directory: $SCRIPT_DIR"
echo "Backend directory: $BACKEND_DIR"

# Navigate to backend directory
cd "$BACKEND_DIR"

# Ensure build directory exists
mkdir -p build
cd build

# Configure with CMake
echo "🔧 Configuring with CMake..."
cmake ..

# Build the project
echo "🔨 Building project..."
cmake --build . -- -j$(nproc)

# Find the executable
echo "🔍 Looking for executable..."

# Check common locations
EXECUTABLE=""
if [ -f "./TrainSimulationApp" ]; then
    EXECUTABLE="./TrainSimulationApp"
elif [ -f "./bin/TrainSimulationApp" ]; then
    EXECUTABLE="./bin/TrainSimulationApp"
elif [ -f "../bin/TrainSimulationApp" ]; then
    EXECUTABLE="../bin/TrainSimulationApp"
else
    # Try to find any executable
    EXECUTABLE=$(find . -type f -executable -name "*TrainSimulation*" | head -1)
fi

if [ -n "$EXECUTABLE" ]; then
    echo "✅ Found executable: $EXECUTABLE"
    echo "🚀 Starting backend server..."
    $EXECUTABLE --headless --port=8080
else
    echo "❌ No executable found!"
    echo "Available files in build directory:"
    find . -type f -executable
    echo "Available files in bin directory (if exists):"
    ls -la ../bin/ 2>/dev/null || echo "No bin directory found"
    exit 1
fi