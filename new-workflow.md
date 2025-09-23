# Qt + Next.js + Electron Integration Guide (Cross-Platform)

This guide explains how to create a desktop application using Next.js + Electron as the frontend while keeping your existing Qt Train Simulation App as the backend service. **Supports both Linux and Windows development/deployment.**

## 📋 Table of Contents

1. [Overview & Architecture](#overview--architecture)
2. [Prerequisites](#prerequisites)
3. [Cross-Platform Considerations](#cross-platform-considerations)
4. [Project Structure](#project-structure)
5. [Step-by-Step Implementation](#step-by-step-implementation)
6. [Qt Backend Modifications](#qt-backend-modifications)
7. [Next.js Frontend Setup](#nextjs-frontend-setup)
8. [Electron Configuration](#electron-configuration)
9. [Communication Layer](#communication-layer)
10. [Cross-Platform Build & Distribution](#cross-platform-build--distribution)
11. [Troubleshooting](#troubleshooting)

---

## 🏗️ Overview & Architecture

### Architecture Flow
```
┌─────────────────┐    HTTP/REST API    ┌──────────────────┐
│   Electron      │ ←──────────────────→ │   Qt Backend     │
│   (Next.js UI)  │    localhost:8080    │   (HTTP Server)  │
└─────────────────┘                     └──────────────────┘
```

### Components Breakdown
- **Electron**: Desktop app container
- **Next.js**: Modern React-based UI framework
- **Qt Backend**: Your existing train simulation logic exposed via HTTP API
- **Communication**: RESTful API over localhost

---

## 🔧 Prerequisites

### Development Environment

#### Common Requirements (Both Platforms)
- **Node.js** (v18+ recommended)
- **npm** or **yarn** package manager
- **Qt 6.x** (your existing setup)
- **CMake 3.16+**
- **Git** for version control

#### Linux-Specific (Nobara/Fedora-based)
```bash
# Install Node.js via NodeSource
curl -fsSL https://rpm.nodesource.com/setup_18.x | sudo bash -
sudo dnf install nodejs

# Install Qt development packages
sudo dnf install qt6-qtbase-devel qt6-qtcharts-devel qt6-qtnetworkauth-devel
sudo dnf install cmake gcc-c++ make

# Install build tools
sudo dnf install rpm-build
```

#### Windows-Specific
- **Qt Creator with MinGW 64-bit** or **MSVC 2022**
- **Visual Studio Build Tools 2022** (recommended)
- **Node.js** from official website
- **Git for Windows**

#### Alternative: Using Qt Online Installer (Cross-Platform)
1. Download Qt Online Installer from qt.io
2. Install Qt 6.5+ with following components:
   - Qt Charts
   - Qt Network Authorization
   - CMake
   - Ninja
   - Compiler (MinGW 64-bit for Windows, GCC for Linux)

### Required Skills
- Basic Qt/C++ knowledge (you already have this)
- JavaScript/TypeScript fundamentals
- Basic understanding of REST APIs
- Node.js basics

---

## 🌐 Cross-Platform Considerations

### Platform Detection & Handling
The application needs to handle platform-specific differences:

1. **Executable Names**
   - Linux: `TrainSimulationApp` (no extension)
   - Windows: `TrainSimulationApp.exe`

2. **Path Separators**
   - Linux: `/` (forward slash)
   - Windows: `\` (backslash) - but Node.js handles this automatically

3. **Build Tools**
   - Linux: GCC, system package managers
   - Windows: MSVC or MinGW, vcpkg (optional)

4. **Distribution**
   - Linux: AppImage, Flatpak, or native packages (.rpm, .deb)
   - Windows: NSIS installer, MSI, or portable executable

### Development Strategy
- **Primary Development**: Linux (your current setup)
- **Cross-Platform Testing**: Use virtual machines or dual-boot
- **CI/CD**: GitHub Actions for automated cross-platform builds
- **Container Option**: Docker for consistent build environments

---

## 📁 Project Structure

```
train-simulation-desktop/
├── backend/                          # Qt Application (your existing app)
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── http_server/                  # New: HTTP server components
│   │   ├── http_server.h
│   │   ├── http_server.cpp
│   │   ├── api_handler.h
│   │   └── api_handler.cpp
│   ├── controllers/
│   ├── models/
│   ├── pages/
│   └── ... (your existing structure)
├── frontend/                         # Electron + Next.js app
│   ├── package.json
│   ├── electron.js                   # Electron main process
│   ├── next.config.js
│   ├── src/
│   │   ├── pages/                    # Next.js pages
│   │   │   ├── index.js
│   │   │   ├── parameters/
│   │   │   ├── simulation/
│   │   │   └── results/
│   │   ├── components/               # React components
│   │   │   ├── ParameterForm/
│   │   │   ├── SimulationChart/
│   │   │   └── Navigation/
│   │   ├── services/                 # API communication
│   │   │   └── api.js
│   │   ├── hooks/                    # React hooks
│   │   └── styles/                   # CSS/styling
│   ├── public/
│   └── electron/
│       ├── main.js                   # Electron main process
│       ├── preload.js               # Electron preload script
│       └── backend-manager.js        # Qt backend lifecycle
├── scripts/                          # Build and deployment scripts
│   ├── build-qt.sh                  # Linux build script
│   ├── build-qt.bat                 # Windows build script
│   ├── build-frontend.sh            # Linux frontend build
│   ├── build-frontend.bat           # Windows frontend build
│   ├── package-app.sh               # Linux packaging
│   ├── package-app.bat              # Windows packaging
│   └── cross-platform-build.js      # Node.js unified build script
├── README.md
└── package.json                      # Root package.json
```

---

## 🚀 Step-by-Step Implementation (Day-by-Day Guide)

### 🗓️ Day 1: Project Structure & Qt Backend Setup

#### Morning: Create Project Structure
```bash
# Navigate to your project root
cd /home/illufoxkasunagi/Documents/NewTrainApp

# Create the new integrated project structure
mkdir -p train-simulation-desktop/{backend,frontend,scripts}

# Copy your existing Qt code to backend
cp -r backend/* train-simulation-desktop/backend/
cp -r CMakeLists.txt train-simulation-desktop/backend/

# Create HTTP server directory
mkdir -p train-simulation-desktop/backend/http_server
```

#### Afternoon: Modify CMakeLists.txt for Headless Build
Create/update `train-simulation-desktop/backend/CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.16)
project(TrainSimulationApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components (NO WIDGETS - only Core and Network)
find_package(Qt6 REQUIRED COMPONENTS Core Network HttpServer)

# Your existing source files (without GUI components)
set(SOURCES
    main.cpp
    core/appcontext.cpp
    controllers/data/electrical_data_handler.cpp
    controllers/data/running_data_handler.cpp
    models/train_data.h
    models/simulation_data.h
    # Add your other model and controller files
    # EXCLUDE: mainwindow/, pages/, widgets/ (GUI components)
    http_server/http_server.cpp
    http_server/api_handler.cpp
)

set(HEADERS
    core/appcontext.h
    controllers/data/electrical_data_handler.h
    controllers/data/running_data_handler.h
    http_server/http_server.h
    http_server/api_handler.h
    # Add other headers (exclude GUI)
)

add_executable(TrainSimulationApp ${SOURCES} ${HEADERS})

target_link_libraries(TrainSimulationApp PRIVATE 
    Qt6::Core
    Qt6::Network
    Qt6::HttpServer
)
```

#### Evening: Create Basic HTTP Server Structure
Create `train-simulation-desktop/backend/http_server/http_server.h`:

```cpp
#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <QObject>
#include <QHttpServer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>
#include "../core/appcontext.h"

class HttpServer : public QObject {
    Q_OBJECT

public:
    explicit HttpServer(AppContext &context, QObject *parent = nullptr);
    bool startServer(int port = 8080);
    void stopServer();

private:
    QHttpServer *m_server;
    AppContext &m_context;
    
    void setupRoutes();
    QJsonObject handleHealthCheck();
    QJsonObject handleParameterUpdate(const QJsonObject &data);
    QJsonObject handleSimulationRun(const QJsonObject &data);
    QJsonObject handleSimulationResults();
};

#endif // HTTP_SERVER_H
```

**✅ Day 1 Goal**: Project structure created, CMakeLists.txt configured for headless build

---

### 🗓️ Day 2: Implement Qt HTTP Server

#### Morning: Implement HTTP Server Class
Create `train-simulation-desktop/backend/http_server/http_server.cpp`:

```cpp
#include "http_server.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

HttpServer::HttpServer(AppContext &context, QObject *parent)
    : QObject(parent), m_context(context) {
    m_server = new QHttpServer(this);
    setupRoutes();
}

bool HttpServer::startServer(int port) {
    const auto result = m_server->listen(QHostAddress::LocalHost, port);
    if (result) {
        qDebug() << "✅ Server started on http://localhost:" << port;
        return true;
    } else {
        qDebug() << "❌ Failed to start server on port" << port;
        return false;
    }
}

void HttpServer::setupRoutes() {
    // Health check endpoint
    m_server->route("/api/health", QHttpServerRequest::Method::Get,
        [this]() {
            return QJsonObject{
                {"status", "ok"}, 
                {"message", "Train Simulation Backend Running"},
                {"version", "1.0.0"}
            };
        });

    // Update train parameters
    m_server->route("/api/parameters/train", QHttpServerRequest::Method::Post,
        [this](const QHttpServerRequest &request) {
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(request.body(), &error);
            
            if (error.error != QJsonParseError::NoError) {
                return QJsonObject{{"error", "Invalid JSON"}};
            }
            
            return handleParameterUpdate(doc.object());
        });

    // Start simulation
    m_server->route("/api/simulation/start", QHttpServerRequest::Method::Post,
        [this](const QHttpServerRequest &request) {
            QJsonParseError error;
            QJsonDocument doc = QJsonDocument::fromJson(request.body(), &error);
            
            if (error.error != QJsonParseError::NoError) {
                return QJsonObject{{"error", "Invalid JSON"}};
            }
            
            return handleSimulationRun(doc.object());
        });

    // Get simulation results
    m_server->route("/api/simulation/results", QHttpServerRequest::Method::Get,
        [this]() {
            return handleSimulationResults();
        });
}

QJsonObject HttpServer::handleParameterUpdate(const QJsonObject &data) {
    // Map to your existing parameter handling
    // Example based on your existing controllers
    if (data.contains("trainParameters")) {
        // Update train data using your existing handlers
        // m_context.updateTrainParameters(data["trainParameters"].toObject());
    }
    
    return QJsonObject{
        {"status", "success"}, 
        {"message", "Parameters updated"}
    };
}

QJsonObject HttpServer::handleSimulationRun(const QJsonObject &data) {
    // Use your existing simulation logic
    // m_context.runSimulation();
    
    return QJsonObject{
        {"status", "success"}, 
        {"message", "Simulation started"}
    };
}

QJsonObject HttpServer::handleSimulationResults() {
    // Return your simulation results
    return QJsonObject{
        {"status", "success"},
        {"results", QJsonArray{/* your results data */}}
    };
}
```

#### Afternoon: Create API Handler for Better Organization
Create `train-simulation-desktop/backend/http_server/api_handler.h`:

```cpp
#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <QObject>
#include <QJsonObject>
#include "../core/appcontext.h"
#include "../controllers/data/electrical_data_handler.h"
#include "../controllers/data/running_data_handler.h"

class ApiHandler : public QObject {
    Q_OBJECT

public:
    explicit ApiHandler(AppContext &context, QObject *parent = nullptr);
    
    // Parameter handling
    QJsonObject updateTrainParameters(const QJsonObject &params);
    QJsonObject updateElectricalParameters(const QJsonObject &params);
    QJsonObject updateRunningParameters(const QJsonObject &params);
    
    // Simulation handling
    QJsonObject startSimulation(const QString &type = "dynamic");
    QJsonObject getSimulationStatus();
    QJsonObject getSimulationResults();
    
    // Data retrieval
    QJsonObject getCurrentParameters();

private:
    AppContext &m_context;
    ElectricalDataHandler *m_electricalHandler;
    RunningDataHandler *m_runningHandler;
    
    // Helper methods
    QJsonObject parametersToJson();
    void jsonToParameters(const QJsonObject &json);
};

#endif // API_HANDLER_H
```

#### Evening: Modify Main.cpp for Headless Operation
Update `train-simulation-desktop/backend/main.cpp`:

```cpp
#include <QCoreApplication>  // Changed from QApplication
#include <QDebug>
#include <QTimer>
#include "core/appcontext.h"
#include "http_server/http_server.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);  // No GUI needed
    
    // Parse command line arguments
    bool serverMode = false;
    int port = 8080;
    
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]) == "--server") {
            serverMode = true;
        } else if (QString(argv[i]) == "--port" && i + 1 < argc) {
            port = QString(argv[i + 1]).toInt();
            i++; // Skip next argument
        }
    }
    
    if (!serverMode) {
        qDebug() << "Usage: TrainSimulationApp --server [--port 8080]";
        return 1;
    }
    
    // Initialize application context
    AppContext context;
    
    // Start HTTP server
    HttpServer server(context);
    if (!server.startServer(port)) {
        qDebug() << "Failed to start server. Exiting.";
        return 1;
    }
    
    qDebug() << "Train Simulation Backend is running...";
    qDebug() << "Press Ctrl+C to stop";
    
    return app.exec();
}
```

**✅ Day 2 Goal**: Basic HTTP server implemented and running headless

---

### 🗓️ Day 3: Build and Test Qt Backend

#### Morning: Build the Qt Backend
```bash
# Navigate to backend directory
cd train-simulation-desktop/backend

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Build
make -j$(nproc)

# Test the server
./TrainSimulationApp --server --port 8080
```

#### Test the API endpoints:
```bash
# In another terminal, test the health endpoint
curl http://localhost:8080/api/health

# Should return: {"status":"ok","message":"Train Simulation Backend Running","version":"1.0.0"}
```

#### Afternoon: Implement API Handler
Create `train-simulation-desktop/backend/http_server/api_handler.cpp`:

```cpp
#include "api_handler.h"
#include <QJsonArray>
#include <QDebug>

ApiHandler::ApiHandler(AppContext &context, QObject *parent)
    : QObject(parent), m_context(context) {
    // Initialize your existing handlers
    m_electricalHandler = new ElectricalDataHandler(context, this);
    m_runningHandler = new RunningDataHandler(context, this);
}

QJsonObject ApiHandler::updateTrainParameters(const QJsonObject &params) {
    try {
        // Map JSON to your existing train data structures
        if (params.contains("tractionMotors")) {
            // m_context.trainData->n_tm = params["tractionMotors"].toDouble();
        }
        if (params.contains("axles")) {
            // m_context.trainData->n_axles = params["axles"].toInt();
        }
        if (params.contains("wheelDiameter")) {
            // m_context.trainData->wheel_diameter = params["wheelDiameter"].toDouble();
        }
        
        return QJsonObject{
            {"status", "success"},
            {"message", "Train parameters updated"}
        };
    } catch (const std::exception &e) {
        return QJsonObject{
            {"status", "error"},
            {"message", QString("Failed to update parameters: %1").arg(e.what())}
        };
    }
}

QJsonObject ApiHandler::updateElectricalParameters(const QJsonObject &params) {
    try {
        // Use your existing electrical data handler
        m_electricalHandler->updateFromJson(params);
        
        return QJsonObject{
            {"status", "success"},
            {"message", "Electrical parameters updated"}
        };
    } catch (const std::exception &e) {
        return QJsonObject{
            {"status", "error"},
            {"message", QString("Failed to update electrical parameters: %1").arg(e.what())}
        };
    }
}

QJsonObject ApiHandler::startSimulation(const QString &type) {
    try {
        // Use your existing simulation logic
        if (type == "dynamic") {
            // m_context.simulationHandler->simulateDynamicTrainMovement();
        } else if (type == "static") {
            // m_context.simulationHandler->simulateStaticCalculation();
        }
        
        return QJsonObject{
            {"status", "success"},
            {"message", "Simulation started"},
            {"type", type}
        };
    } catch (const std::exception &e) {
        return QJsonObject{
            {"status", "error"},
            {"message", QString("Simulation failed: %1").arg(e.what())}
        };
    }
}

QJsonObject ApiHandler::getSimulationResults() {
    try {
        // Convert your simulation results to JSON
        QJsonObject results;
        
        // Example structure - adapt to your actual results
        QJsonArray speedData;
        QJsonArray timeData;
        QJsonArray powerData;
        
        // Fill with your actual simulation data
        // for (const auto &point : m_context.simulationResults->speedProfile) {
        //     speedData.append(point.speed);
        //     timeData.append(point.time);
        // }
        
        results["speedProfile"] = speedData;
        results["timeProfile"] = timeData;
        results["powerProfile"] = powerData;
        
        return QJsonObject{
            {"status", "success"},
            {"results", results}
        };
    } catch (const std::exception &e) {
        return QJsonObject{
            {"status", "error"},
            {"message", QString("Failed to get results: %1").arg(e.what())}
        };
    }
}
```

#### Evening: Test Complete Backend
```bash
# Test parameter update
curl -X POST http://localhost:8080/api/parameters/train \
  -H "Content-Type: application/json" \
  -d '{"tractionMotors": 4, "axles": 8, "wheelDiameter": 860}'

# Test simulation start
curl -X POST http://localhost:8080/api/simulation/start \
  -H "Content-Type: application/json" \
  -d '{"type": "dynamic"}'

# Test results retrieval
curl http://localhost:8080/api/simulation/results
```

**✅ Day 3 Goal**: Qt backend running and responding to API calls

---

### 🗓️ Day 4: Basic Electron Setup (Test Integration First)

#### Morning: Create Minimal Electron App
```bash
# Navigate to frontend directory
cd /home/illufoxkasunagi/Documents/NewTrainApp/frontend

# Initialize Next.js project (if not done already)
npx create-next-app@latest . --typescript --tailwind --eslint --app --src-dir

# Install Electron dependencies
npm install --save-dev electron electron-builder concurrently wait-on cross-env
npm install --save-dev @types/electron electron-is-dev
```

#### Create Basic Electron Main Process
Create `frontend/electron/main.js`:

```javascript
const { app, BrowserWindow } = require('electron');
const { spawn } = require('child_process');
const path = require('path');
const isDev = require('electron-is-dev');

let mainWindow;
let qtBackendProcess;

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1200,
    height: 800,
    webPreferences: {
      nodeIntegration: false,
      contextIsolation: true,
      preload: path.join(__dirname, 'preload.js')
    },
    show: false // Don't show until ready
  });

  const startUrl = isDev 
    ? 'http://localhost:3000' 
    : `file://${path.join(__dirname, '../out/index.html')}`;
  
  mainWindow.loadURL(startUrl);

  mainWindow.once('ready-to-show', () => {
    mainWindow.show();
  });

  if (isDev) {
    mainWindow.webContents.openDevTools();
  }
}

function startQtBackend() {
  const isWindows = process.platform === 'win32';
  const executableName = isWindows ? 'TrainSimulationApp.exe' : 'TrainSimulationApp';
  
  const backendPath = path.join(__dirname, '../../backend/build', executableName);
  
  console.log('Starting Qt backend from:', backendPath);
  
  qtBackendProcess = spawn(backendPath, ['--server', '--port', '8080'], {
    stdio: ['pipe', 'pipe', 'pipe'],
  });

  qtBackendProcess.stdout.on('data', (data) => {
    console.log(`Qt Backend: ${data}`);
  });

  qtBackendProcess.stderr.on('data', (data) => {
    console.error(`Qt Backend Error: ${data}`);
  });
}

app.whenReady().then(() => {
  startQtBackend();
  
  // Wait a bit for backend to start
  setTimeout(() => {
    createWindow();
  }, 2000);
});

app.on('window-all-closed', () => {
  if (qtBackendProcess) {
    qtBackendProcess.kill();
  }
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('before-quit', () => {
  if (qtBackendProcess) {
    qtBackendProcess.kill();
  }
});
```

#### Afternoon: Create Preload Script and Test
Create `frontend/electron/preload.js`:

```javascript
const { contextBridge } = require('electron');

contextBridge.exposeInMainWorld('electronAPI', {
  platform: process.platform,
  getVersion: () => process.env.npm_package_version || '1.0.0',
});
```

#### Update Package.json Scripts
Update `frontend/package.json`:

```json
{
  "main": "electron/main.js",
  "scripts": {
    "dev": "next dev",
    "build": "next build",
    "export": "next export",
    "electron": "wait-on http://localhost:3000 && electron .",
    "electron-dev": "concurrently \"npm run dev\" \"wait-on http://localhost:3000 && electron .\"",
    "dist": "npm run build && npm run export && electron-builder"
  }
}
```

#### Evening: Test Basic Integration
```bash
# Terminal 1: Make sure Qt backend is built and running
cd /home/illufoxkasunagi/Documents/NewTrainApp/backend/build
./TrainSimulationApp --server

# Terminal 2: Test Electron app
cd /home/illufoxkasunagi/Documents/NewTrainApp/frontend
npm run electron-dev
```

**✅ Day 4 Goal**: Basic Electron app opens Next.js content and can manage Qt backend

---

### 🗓️ Day 5: Test Backend Connection from Electron

#### Morning: Create API Service with Health Check
Create `frontend/src/services/api.ts`:

```typescript
import axios, { AxiosInstance } from 'axios';

const API_BASE_URL = 'http://localhost:8080';

class TrainSimulationAPI {
  private client: AxiosInstance;

  constructor() {
    this.client = axios.create({
      baseURL: API_BASE_URL,
      timeout: 5000,
      headers: {
        'Content-Type': 'application/json',
      },
    });
  }

  // Health check
  async checkHealth(): Promise<{ status: string; message: string }> {
    const response = await this.client.get('/api/health');
    return response.data;
  }

  // Test parameter update
  async testParameterUpdate(): Promise<any> {
    const testParams = {
      tractionMotors: 4,
      axles: 8,
      wheelDiameter: 860
    };
    const response = await this.client.post('/api/parameters/train', testParams);
    return response.data;
  }
}

export const api = new TrainSimulationAPI();
```

#### Create Simple Connection Test Page
Update `frontend/src/app/page.tsx`:

```tsx
'use client';

import { useState, useEffect } from 'react';
import { api } from '@/services/api';

export default function Home() {
  const [backendStatus, setBackendStatus] = useState<string>('Checking...');
  const [testResult, setTestResult] = useState<string>('');

  useEffect(() => {
    checkBackendConnection();
  }, []);

  const checkBackendConnection = async () => {
    try {
      const health = await api.checkHealth();
      setBackendStatus(`✅ Backend Connected: ${health.message}`);
    } catch (error) {
      setBackendStatus(`❌ Backend Error: ${error.message}`);
    }
  };

  const testParameterUpdate = async () => {
    try {
      const result = await api.testParameterUpdate();
      setTestResult(`✅ Parameter Update: ${result.message}`);
    } catch (error) {
      setTestResult(`❌ Parameter Error: ${error.message}`);
    }
  };

  return (
    <div className="container mx-auto p-8">
      <h1 className="text-3xl font-bold mb-8">Train Simulation App</h1>
      
      <div className="space-y-4">
        <div className="p-4 border rounded">
          <h2 className="text-xl font-semibold mb-2">Backend Status</h2>
          <p className="mb-4">{backendStatus}</p>
          <button 
            onClick={checkBackendConnection}
            className="px-4 py-2 bg-blue-500 text-white rounded hover:bg-blue-600"
          >
            Refresh Connection
          </button>
        </div>

        <div className="p-4 border rounded">
          <h2 className="text-xl font-semibold mb-2">Test API</h2>
          <p className="mb-4">{testResult}</p>
          <button 
            onClick={testParameterUpdate}
            className="px-4 py-2 bg-green-500 text-white rounded hover:bg-green-600"
          >
            Test Parameter Update
          </button>
        </div>
      </div>
    </div>
  );
}
```

#### Afternoon: Add axios Dependency and Test
```bash
# Install axios
npm install axios

# Test the connection
npm run electron-dev
```

#### Evening: Debug and Fix Connection Issues
Create `frontend/src/utils/debug.ts`:

```typescript
export const debugAPI = {
  async testEndpoints() {
    const endpoints = [
      '/api/health',
      '/api/parameters/train',
      '/api/simulation/start',
      '/api/simulation/results'
    ];

    const results = [];
    
    for (const endpoint of endpoints) {
      try {
        const response = await fetch(`http://localhost:8080${endpoint}`, {
          method: endpoint.includes('parameters') || endpoint.includes('simulation/start') ? 'POST' : 'GET',
          headers: { 'Content-Type': 'application/json' },
          body: endpoint.includes('parameters') ? JSON.stringify({ test: true }) : undefined
        });
        
        results.push({
          endpoint,
          status: response.status,
          success: response.ok
        });
      } catch (error) {
        results.push({
          endpoint,
          status: 'ERROR',
          success: false,
          error: error.message
        });
      }
    }
    
    return results;
  }
};
```

**✅ Day 5 Goal**: Electron app successfully communicates with Qt backend API

---

### 🗓️ Day 6: Build Parameter Input Forms

#### Morning: Install UI Components
```bash
# Install shadcn/ui components (you already started this)
npx shadcn@latest add card input label button select
npx shadcn@latest add tabs toast

# Install additional dependencies
npm install @tanstack/react-query lucide-react
```

#### Create Parameter Form Component
Create `frontend/src/components/forms/TrainParameterForm.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Button } from '@/components/ui/button';
import { api } from '@/services/api';

interface TrainParameters {
  tractionMotors: number;
  axles: number;
  wheelDiameter: number;
  gearRatio: number;
  loadPerCar: number;
  passengerWeight: number;
}

export default function TrainParameterForm() {
  const [parameters, setParameters] = useState<TrainParameters>({
    tractionMotors: 4,
    axles: 8,
    wheelDiameter: 860,
    gearRatio: 4.5,
    loadPerCar: 12000,
    passengerWeight: 68,
  });

  const [status, setStatus] = useState<string>('');
  const [isSubmitting, setIsSubmitting] = useState(false);

  const handleInputChange = (field: keyof TrainParameters, value: string) => {
    setParameters(prev => ({
      ...prev,
      [field]: parseFloat(value) || 0
    }));
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setIsSubmitting(true);
    setStatus('Updating parameters...');

    try {
      const result = await api.testParameterUpdate();
      setStatus(`✅ Success: ${result.message}`);
    } catch (error) {
      setStatus(`❌ Error: ${error.message}`);
    } finally {
      setIsSubmitting(false);
    }
  };

  return (
    <Card className="w-full max-w-2xl">
      <CardHeader>
        <CardTitle>Train Parameters</CardTitle>
      </CardHeader>
      <CardContent>
        <form onSubmit={handleSubmit} className="space-y-4">
          <div className="grid grid-cols-2 gap-4">
            <div>
              <Label htmlFor="tractionMotors">Traction Motors</Label>
              <Input
                id="tractionMotors"
                type="number"
                value={parameters.tractionMotors}
                onChange={(e) => handleInputChange('tractionMotors', e.target.value)}
              />
            </div>
            
            <div>
              <Label htmlFor="axles">Number of Axles</Label>
              <Input
                id="axles"
                type="number"
                value={parameters.axles}
                onChange={(e) => handleInputChange('axles', e.target.value)}
              />
            </div>
            
            <div>
              <Label htmlFor="wheelDiameter">Wheel Diameter (mm)</Label>
              <Input
                id="wheelDiameter"
                type="number"
                value={parameters.wheelDiameter}
                onChange={(e) => handleInputChange('wheelDiameter', e.target.value)}
              />
            </div>
            
            <div>
              <Label htmlFor="gearRatio">Gear Ratio</Label>
              <Input
                id="gearRatio"
                type="number"
                step="0.1"
                value={parameters.gearRatio}
                onChange={(e) => handleInputChange('gearRatio', e.target.value)}
              />
            </div>
            
            <div>
              <Label htmlFor="loadPerCar">Load per Car (kg)</Label>
              <Input
                id="loadPerCar"
                type="number"
                value={parameters.loadPerCar}
                onChange={(e) => handleInputChange('loadPerCar', e.target.value)}
              />
            </div>
            
            <div>
              <Label htmlFor="passengerWeight">Passenger Weight (kg)</Label>
              <Input
                id="passengerWeight"
                type="number"
                value={parameters.passengerWeight}
                onChange={(e) => handleInputChange('passengerWeight', e.target.value)}
              />
            </div>
          </div>

          <Button type="submit" disabled={isSubmitting} className="w-full">
            {isSubmitting ? 'Updating...' : 'Update Parameters'}
          </Button>

          {status && (
            <div className="mt-4 p-3 border rounded">
              <p className="text-sm">{status}</p>
            </div>
          )}
        </form>
      </CardContent>
    </Card>
  );
}
```

#### Afternoon: Create Simulation Control Component
Create `frontend/src/components/forms/SimulationControl.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from '@/components/ui/select';
import { Play, Square } from 'lucide-react';
import { api } from '@/services/api';

export default function SimulationControl() {
  const [simulationType, setSimulationType] = useState<'dynamic' | 'static'>('dynamic');
  const [status, setStatus] = useState<string>('Ready');
  const [isRunning, setIsRunning] = useState(false);

  const handleStartSimulation = async () => {
    setIsRunning(true);
    setStatus('Starting simulation...');

    try {
      // For now, just test the connection
      const health = await api.checkHealth();
      setStatus(`✅ Simulation would start: ${health.message}`);
      
      // Simulate some processing time
      setTimeout(() => {
        setStatus('✅ Simulation completed (test mode)');
        setIsRunning(false);
      }, 3000);
      
    } catch (error) {
      setStatus(`❌ Error: ${error.message}`);
      setIsRunning(false);
    }
  };

  return (
    <Card className="w-full max-w-md">
      <CardHeader>
        <CardTitle>Simulation Control</CardTitle>
      </CardHeader>
      <CardContent className="space-y-4">
        <div>
          <label className="text-sm font-medium mb-2 block">Simulation Type</label>
          <Select value={simulationType} onValueChange={(value: 'dynamic' | 'static') => setSimulationType(value)}>
            <SelectTrigger>
              <SelectValue />
            </SelectTrigger>
            <SelectContent>
              <SelectItem value="dynamic">Dynamic</SelectItem>
              <SelectItem value="static">Static</SelectItem>
            </SelectContent>
          </Select>
        </div>

        <Button 
          onClick={handleStartSimulation} 
          disabled={isRunning}
          className="w-full"
        >
          <Play className="w-4 h-4 mr-2" />
          {isRunning ? 'Running...' : 'Start Simulation'}
        </Button>

        <div className="p-3 border rounded">
          <p className="text-sm">{status}</p>
        </div>
      </CardContent>
    </Card>
  );
}
```

#### Evening: Update Main Page with Tabs
Update `frontend/src/app/page.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs';
import TrainParameterForm from '@/components/forms/TrainParameterForm';
import SimulationControl from '@/components/forms/SimulationControl';

export default function Home() {
  return (
    <div className="container mx-auto p-8">
      <h1 className="text-3xl font-bold mb-8">Train Simulation App</h1>
      
      <Tabs defaultValue="parameters" className="space-y-4">
        <TabsList className="grid w-full grid-cols-3">
          <TabsTrigger value="parameters">Parameters</TabsTrigger>
          <TabsTrigger value="simulation">Simulation</TabsTrigger>
          <TabsTrigger value="results">Results</TabsTrigger>
        </TabsList>

        <TabsContent value="parameters" className="space-y-4">
          <TrainParameterForm />
        </TabsContent>

        <TabsContent value="simulation" className="space-y-4">
          <div className="flex justify-center">
            <SimulationControl />
          </div>
        </TabsContent>

        <TabsContent value="results" className="space-y-4">
          <div className="text-center p-8 border border-dashed rounded">
            <p className="text-muted-foreground">Results will appear here after simulation</p>
          </div>
        </TabsContent>
      </Tabs>
    </div>
  );
}
```

**✅ Day 6 Goal**: Basic UI with parameter forms and simulation controls working

---

### 🗓️ Day 7: Add Results Visualization

#### Morning: Install Chart Dependencies
```bash
npm install recharts
npm install @types/recharts
```

#### Create Results Component
Create `frontend/src/components/charts/SimulationResults.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';
import { RefreshCw, Download } from 'lucide-react';

// Mock data for testing
const mockChartData = [
  { time: 0, speed: 0, power: 0, energy: 0 },
  { time: 10, speed: 20, power: 150, energy: 25 },
  { time: 20, speed: 40, power: 300, energy: 75 },
  { time: 30, speed: 60, power: 450, energy: 150 },
  { time: 40, speed: 80, power: 600, energy: 250 },
  { time: 50, speed: 100, power: 750, energy: 375 },
  { time: 60, speed: 100, power: 500, energy: 425 },
  { time: 70, speed: 80, power: 300, energy: 450 },
  { time: 80, speed: 60, power: 200, energy: 470 },
  { time: 90, speed: 40, power: 150, energy: 485 },
  { time: 100, speed: 0, power: 0, energy: 500 },
];

export default function SimulationResults() {
  const [hasResults, setHasResults] = useState(false);

  const generateMockResults = () => {
    setHasResults(true);
  };

  const exportResults = () => {
    const dataStr = JSON.stringify(mockChartData, null, 2);
    const dataBlob = new Blob([dataStr], { type: 'application/json' });
    const url = URL.createObjectURL(dataBlob);
    const link = document.createElement('a');
    link.href = url;
    link.download = 'simulation_results.json';
    link.click();
  };

  if (!hasResults) {
    return (
      <div className="text-center p-8 border border-dashed rounded">
        <p className="text-muted-foreground mb-4">No simulation results yet</p>
        <Button onClick={generateMockResults}>
          Generate Mock Results (for testing)
        </Button>
      </div>
    );
  }

  return (
    <div className="space-y-6">
      <div className="flex justify-between items-center">
        <h2 className="text-2xl font-bold">Simulation Results</h2>
        <div className="space-x-2">
          <Button variant="outline" onClick={() => setHasResults(false)}>
            <RefreshCw className="w-4 h-4 mr-2" />
            Clear Results
          </Button>
          <Button onClick={exportResults}>
            <Download className="w-4 h-4 mr-2" />
            Export Data
          </Button>
        </div>
      </div>

      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        <Card>
          <CardHeader>
            <CardTitle>Speed Profile</CardTitle>
          </CardHeader>
          <CardContent>
            <ResponsiveContainer width="100%" height={300}>
              <LineChart data={mockChartData}>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey="time" label={{ value: 'Time (s)', position: 'insideBottom', offset: -10 }} />
                <YAxis label={{ value: 'Speed (km/h)', angle: -90, position: 'insideLeft' }} />
                <Tooltip />
                <Legend />
                <Line type="monotone" dataKey="speed" stroke="#8884d8" strokeWidth={2} />
              </LineChart>
            </ResponsiveContainer>
          </CardContent>
        </Card>

        <Card>
          <CardHeader>
            <CardTitle>Power Profile</CardTitle>
          </CardHeader>
          <CardContent>
            <ResponsiveContainer width="100%" height={300}>
              <LineChart data={mockChartData}>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey="time" label={{ value: 'Time (s)', position: 'insideBottom', offset: -10 }} />
                <YAxis label={{ value: 'Power (kW)', angle: -90, position: 'insideLeft' }} />
                <Tooltip />
                <Legend />
                <Line type="monotone" dataKey="power" stroke="#82ca9d" strokeWidth={2} />
              </LineChart>
            </ResponsiveContainer>
          </CardContent>
        </Card>

        <Card className="lg:col-span-2">
          <CardHeader>
            <CardTitle>Energy Consumption</CardTitle>
          </CardHeader>
          <CardContent>
            <ResponsiveContainer width="100%" height={300}>
              <LineChart data={mockChartData}>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey="time" label={{ value: 'Time (s)', position: 'insideBottom', offset: -10 }} />
                <YAxis label={{ value: 'Energy (kWh)', angle: -90, position: 'insideLeft' }} />
                <Tooltip />
                <Legend />
                <Line type="monotone" dataKey="energy" stroke="#ffc658" strokeWidth={2} />
              </LineChart>
            </ResponsiveContainer>
          </CardContent>
        </Card>
      </div>

      <Card>
        <CardHeader>
          <CardTitle>Summary Statistics</CardTitle>
        </CardHeader>
        <CardContent>
          <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
            <div className="text-center">
              <p className="text-2xl font-bold text-blue-600">100</p>
              <p className="text-sm text-muted-foreground">Max Speed (km/h)</p>
            </div>
            <div className="text-center">
              <p className="text-2xl font-bold text-green-600">750</p>
              <p className="text-sm text-muted-foreground">Peak Power (kW)</p>
            </div>
            <div className="text-center">
              <p className="text-2xl font-bold text-yellow-600">500</p>
              <p className="text-sm text-muted-foreground">Total Energy (kWh)</p>
            </div>
            <div className="text-center">
              <p className="text-2xl font-bold text-purple-600">100</p>
              <p className="text-sm text-muted-foreground">Total Time (s)</p>
            </div>
          </div>
        </CardContent>
      </Card>
    </div>
  );
}
```

#### Afternoon: Update Main Page with Results
Update the results tab in `frontend/src/app/page.tsx`:

```tsx
import SimulationResults from '@/components/charts/SimulationResults';

// In the TabsContent for results:
<TabsContent value="results" className="space-y-4">
  <SimulationResults />
</TabsContent>
```

#### Evening: Test Full UI Flow
```bash
# Run the complete application
npm run electron-dev
```

Test the complete flow:
1. Open Parameters tab → Enter values
2. Open Simulation tab → Start simulation
3. Open Results tab → View charts and data

**✅ Day 7 Goal**: Complete UI with working charts and data visualization

---

### 🗓️ Day 8: Create Build Scripts

#### Morning: Create Development Scripts
Create `scripts/build-dev.sh`:

```bash
#!/bin/bash
set -e

echo "🔧 Setting up development environment..."

# Build Qt Backend
echo "📦 Building Qt Backend..."
cd backend
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)

if [ -f "TrainSimulationApp" ]; then
    echo "✅ Qt Backend built successfully"
    chmod +x TrainSimulationApp
else
    echo "❌ Qt Backend build failed"
    exit 1
fi

cd ../..

# Setup Frontend
echo "🌐 Setting up Frontend..."
cd frontend

# Install dependencies if needed
if [ ! -d "node_modules" ]; then
    echo "Installing npm dependencies..."
    npm install
fi

echo "✅ Development environment ready!"
echo ""
echo "🚀 To start development:"
echo "   ./scripts/start-dev.sh"
```

Create `scripts/start-dev.sh`:

```bash
#!/bin/bash

echo "🚀 Starting Train Simulation App in development mode..."

# Function to cleanup background processes
cleanup() {
    echo ""
    echo "🛑 Stopping services..."
    if [ ! -z "$BACKEND_PID" ] && kill -0 $BACKEND_PID 2>/dev/null; then
        kill $BACKEND_PID
        echo "✅ Backend stopped"
    fi
    if [ ! -z "$FRONTEND_PID" ] && kill -0 $FRONTEND_PID 2>/dev/null; then
        kill $FRONTEND_PID
        echo "✅ Frontend stopped"
    fi
    exit 0
}

# Trap Ctrl+C
trap cleanup SIGINT

# Start Qt Backend
echo "📦 Starting Qt Backend..."
cd backend/build
if [ ! -f "TrainSimulationApp" ]; then
    echo "❌ Backend not built. Run ./scripts/build-dev.sh first"
    exit 1
fi

./TrainSimulationApp --server &
BACKEND_PID=$!
cd ../..

# Wait for backend to start
echo "⏳ Waiting for backend to start..."
sleep 3

# Test backend health
if curl -s http://localhost:8080/api/health > /dev/null; then
    echo "✅ Backend is responding"
else
    echo "⚠️  Backend may not be ready yet"
fi

# Start Frontend
echo "🌐 Starting Frontend..."
cd frontend
npm run electron-dev &
FRONTEND_PID=$!
cd ..

echo ""
echo "✅ Services starting..."
echo "🔍 Backend API: http://localhost:8080/api/health"
echo "🎨 Frontend will open automatically"
echo ""
echo "Press Ctrl+C to stop all services"

# Wait for user to stop
wait
```

#### Afternoon: Create Production Build Script
Create `scripts/build-production.sh`:

```bash
#!/bin/bash
set -e

echo "🏭 Building for production..."

# Clean previous builds
echo "🧹 Cleaning previous builds..."
rm -rf backend/build
rm -rf frontend/out
rm -rf frontend/dist

# Build backend in release mode
echo ""
echo "📦 Building Qt Backend (Release)..."
cd backend
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3"
make -j$(nproc)

# Strip debug symbols to reduce size
if [ -f "TrainSimulationApp" ]; then
    strip TrainSimulationApp
    echo "✅ Backend built: $(du -h TrainSimulationApp | cut -f1)"
else
    echo "❌ Backend build failed"
    exit 1
fi

cd ../..

# Build frontend for production
echo ""
echo "🌐 Building Frontend (Production)..."
cd frontend

# Install dependencies
npm ci --production=false

# Build Next.js app
NODE_ENV=production npm run build

# Build Electron app
echo ""
echo "📱 Packaging Electron App..."
npm run dist

# Show build results
echo ""
echo "🎉 Production build complete!"
echo ""
echo "📊 Build results:"
if [ -d "dist" ]; then
    find dist -type f \( -name "*.AppImage" -o -name "*.deb" -o -name "*.rpm" \) | while read file; do
        echo "  $(basename "$file"): $(du -h "$file" | cut -f1)"
    done
else
    echo "❌ No distribution packages found"
fi

cd ..

echo ""
echo "✅ Ready for distribution!"
echo "📁 Packages are in: frontend/dist/"
```

#### Evening: Update Electron Builder Configuration
Add to `frontend/package.json`:

```json
{
  "build": {
    "appId": "com.trainSimulation.app",
    "productName": "Train Simulation App",
    "directories": {
      "output": "dist"
    },
    "files": [
      "out/**/*",
      "electron/**/*",
      "node_modules/**/*"
    ],
    "extraResources": [
      {
        "from": "../backend/build/TrainSimulationApp",
        "to": "backend/TrainSimulationApp"
      }
    ],
    "linux": {
      "target": [
        "AppImage",
        "deb",
        "rpm"
      ],
      "category": "Science"
    },
    "win": {
      "target": "nsis",
      "icon": "public/icon.ico"
    }
  }
}
```

Make scripts executable:
```bash
chmod +x scripts/*.sh
```

**✅ Day 8 Goal**: Complete build system with development and production scripts

---

### 🗓️ Day 9: Testing and Error Handling

#### Morning: Add Error Boundaries
Create `frontend/src/components/common/ErrorBoundary.tsx`:

```tsx
'use client';

import React from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { AlertTriangle, RefreshCw } from 'lucide-react';

interface ErrorBoundaryState {
  hasError: boolean;
  error?: Error;
}

export class ErrorBoundary extends React.Component<
  React.PropsWithChildren<{}>,
  ErrorBoundaryState
> {
  constructor(props: React.PropsWithChildren<{}>) {
    super(props);
    this.state = { hasError: false };
  }

  static getDerivedStateFromError(error: Error): ErrorBoundaryState {
    return { hasError: true, error };
  }

  componentDidCatch(error: Error, errorInfo: React.ErrorInfo) {
    console.error('ErrorBoundary caught an error:', error, errorInfo);
  }

  handleReset = () => {
    this.setState({ hasError: false, error: undefined });
  };

  render() {
    if (this.state.hasError) {
      return (
        <div className="min-h-screen flex items-center justify-center p-4">
          <Card className="w-full max-w-md">
            <CardHeader>
              <CardTitle className="flex items-center gap-2 text-red-600">
                <AlertTriangle className="w-5 h-5" />
                Something went wrong
              </CardTitle>
            </CardHeader>
            <CardContent className="space-y-4">
              <p className="text-sm text-muted-foreground">
                The application encountered an unexpected error.
              </p>
              
              {this.state.error && (
                <details className="text-xs bg-gray-100 p-2 rounded">
                  <summary className="cursor-pointer font-medium">Error Details</summary>
                  <pre className="mt-2 whitespace-pre-wrap">
                    {this.state.error.message}
                  </pre>
                </details>
              )}

              <div className="flex gap-2">
                <Button onClick={this.handleReset} className="flex-1">
                  <RefreshCw className="w-4 h-4 mr-2" />
                  Try Again
                </Button>
                <Button 
                  variant="outline" 
                  onClick={() => window.location.reload()}
                  className="flex-1"
                >
                  Reload App
                </Button>
              </div>
            </CardContent>
          </Card>
        </div>
      );
    }

    return this.props.children;
  }
}
```

#### Create Integration Test Script
Create `scripts/test-integration.sh`:

```bash
#!/bin/bash
set -e

echo "🧪 Running integration tests..."

# Start backend for testing
echo "📦 Starting backend for testing..."
cd backend/build
if [ ! -f "TrainSimulationApp" ]; then
    echo "❌ Backend not built. Run ./scripts/build-dev.sh first"
    exit 1
fi

./TrainSimulationApp --server &
BACKEND_PID=$!
cd ../..

# Wait for backend to start
echo "⏳ Waiting for backend..."
sleep 5

# Test API endpoints
echo ""
echo "🌐 Testing API endpoints..."

test_endpoint() {
    local endpoint=$1
    local method=${2:-GET}
    local data=${3:-}
    
    echo -n "Testing $method $endpoint... "
    
    if [ "$method" = "POST" ] && [ -n "$data" ]; then
        response=$(curl -s -w "%{http_code}" -X POST \
            -H "Content-Type: application/json" \
            -d "$data" \
            "http://localhost:8080$endpoint" || echo "000")
    else
        response=$(curl -s -w "%{http_code}" "http://localhost:8080$endpoint" || echo "000")
    fi
    
    http_code="${response: -3}"
    
    if [ "$http_code" = "200" ]; then
        echo "✅ OK"
        return 0
    else
        echo "❌ Failed ($http_code)"
        return 1
    fi
}

# Run tests
PASSED=0
TOTAL=0

# Test health endpoint
((TOTAL++))
if test_endpoint "/api/health"; then
    ((PASSED++))
fi

# Test parameter update
((TOTAL++))
if test_endpoint "/api/parameters/train" "POST" '{"tractionMotors": 4, "axles": 8}'; then
    ((PASSED++))
fi

# Test simulation start
((TOTAL++))
if test_endpoint "/api/simulation/start" "POST" '{"type": "dynamic"}'; then
    ((PASSED++))
fi

# Test results
((TOTAL++))
if test_endpoint "/api/simulation/results"; then
    ((PASSED++))
fi

# Cleanup
echo ""
echo "🛑 Stopping backend..."
kill $BACKEND_PID

echo ""
echo "📊 Test Results: $PASSED/$TOTAL tests passed"

if [ $PASSED -eq $TOTAL ]; then
    echo "✅ All tests passed!"
    exit 0
else
    echo "❌ Some tests failed"
    exit 1
fi
```

#### Afternoon: Create Health Check Component
Create `frontend/src/components/common/HealthCheck.tsx`:

```tsx
'use client';

import { useState, useEffect } from 'react';
import { Card, CardContent } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { CheckCircle, XCircle, Clock } from 'lucide-react';
import { api } from '@/services/api';

export default function HealthCheck() {
  const [status, setStatus] = useState<'checking' | 'connected' | 'error'>('checking');
  const [message, setMessage] = useState('Checking backend connection...');

  const checkHealth = async () => {
    setStatus('checking');
    setMessage('Checking backend connection...');

    try {
      const health = await api.checkHealth();
      setStatus('connected');
      setMessage(health.message);
    } catch (error) {
      setStatus('error');
      setMessage(`Connection failed: ${error.message}`);
    }
  };

  useEffect(() => {
    checkHealth();
    
    // Check health every 30 seconds
    const interval = setInterval(checkHealth, 30000);
    return () => clearInterval(interval);
  }, []);

  const getStatusIcon = () => {
    switch (status) {
      case 'checking':
        return <Clock className="w-4 h-4 text-yellow-500 animate-spin" />;
      case 'connected':
        return <CheckCircle className="w-4 h-4 text-green-500" />;
      case 'error':
        return <XCircle className="w-4 h-4 text-red-500" />;
    }
  };

  const getStatusColor = () => {
    switch (status) {
      case 'checking':
        return 'border-yellow-200 bg-yellow-50';
      case 'connected':
        return 'border-green-200 bg-green-50';
      case 'error':
        return 'border-red-200 bg-red-50';
    }
  };

  return (
    <Card className={`${getStatusColor()} border`}>
      <CardContent className="p-3">
        <div className="flex items-center justify-between">
          <div className="flex items-center gap-2">
            {getStatusIcon()}
            <span className="text-sm font-medium">Backend Status</span>
          </div>
          
          <div className="flex items-center gap-2">
            <span className="text-xs text-muted-foreground">{message}</span>
            {status === 'error' && (
              <Button size="sm" variant="outline" onClick={checkHealth}>
                Retry
              </Button>
            )}
          </div>
        </div>
      </CardContent>
    </Card>
  );
}
```

#### Evening: Add Health Check to Main Layout
Update `frontend/src/app/page.tsx` to include the health check:

```tsx
import HealthCheck from '@/components/common/HealthCheck';
import { ErrorBoundary } from '@/components/common/ErrorBoundary';

export default function Home() {
  return (
    <ErrorBoundary>
      <div className="container mx-auto p-8">
        <h1 className="text-3xl font-bold mb-4">Train Simulation App</h1>
        
        <div className="mb-6">
          <HealthCheck />
        </div>
        
        {/* Rest of your existing content */}
      </div>
    </ErrorBoundary>
  );
}
```

Make test script executable:
```bash
chmod +x scripts/test-integration.sh
```

**✅ Day 9 Goal**: Error handling, health monitoring, and integration testing complete

---

### 🗓️ Day 10: Final Polish and Documentation

#### Morning: Create Final Documentation
Create `README.md`:

```markdown
# Train Simulation Desktop App

A modern desktop application for train simulation and analysis, built with Qt backend and Next.js + Electron frontend.

## 🚀 Quick Start

### Prerequisites
- Qt 6.x with development tools
- Node.js 18+
- CMake 3.16+

### Development Setup
```bash
# Clone and setup
git clone <your-repo>
cd train-simulation-desktop

# Build and start development environment
./scripts/build-dev.sh
./scripts/start-dev.sh
```

### Production Build
```bash
./scripts/build-production.sh
```

## 🏗️ Architecture

- **Qt Backend**: Headless HTTP server exposing simulation APIs
- **Next.js Frontend**: Modern React-based user interface
- **Electron**: Desktop application wrapper

## 📁 Project Structure

```
├── backend/          # Qt C++ application
├── frontend/         # Next.js + Electron app
├── scripts/          # Build and development scripts
└── README.md
```

## 🔧 Development

### Available Scripts

- `./scripts/build-dev.sh` - Setup development environment
- `./scripts/start-dev.sh` - Start development servers
- `./scripts/build-production.sh` - Build for production
- `./scripts/test-integration.sh` - Run integration tests

### API Endpoints

- `GET /api/health` - Backend health check
- `POST /api/parameters/train` - Update train parameters
- `POST /api/simulation/start` - Start simulation
- `GET /api/simulation/results` - Get simulation results

## 🐛 Troubleshooting

### Backend Won't Start
```bash
# Check if built correctly
ls -la backend/build/TrainSimulationApp

# Check dependencies
ldd backend/build/TrainSimulationApp

# Test manually
./backend/build/TrainSimulationApp --server
```

### Frontend Issues
```bash
# Reinstall dependencies
cd frontend
rm -rf node_modules package-lock.json
npm install

# Check Electron
npm run electron-dev
```

## 📦 Distribution

Built packages are available in `frontend/dist/`:
- Linux: `.AppImage`, `.deb`, `.rpm`
- Windows: `.exe` installer

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run tests: `./scripts/test-integration.sh`
5. Submit a pull request

## 📄 License

[Your License Here]
```

#### Create User Manual
Create `USER_MANUAL.md`:

```markdown
# Train Simulation App - User Manual

## Getting Started

### Installation

#### Linux
1. Download the `.AppImage` file
2. Make it executable: `chmod +x TrainSimulationApp.AppImage`
3. Run: `./TrainSimulationApp.AppImage`

#### Windows
1. Download the installer `.exe`
2. Run as administrator
3. Follow installation wizard

### First Launch

When you first open the app:
1. The backend will start automatically
2. The app will check connection status
3. You'll see a green status indicator when ready

## Using the Application

### 1. Setting Parameters

**Train Parameters Tab:**
- **Traction Motors**: Number of motors (typically 4-8)
- **Axles**: Number of axles (typically 6-12)
- **Wheel Diameter**: In millimeters (typically 860-1200mm)
- **Gear Ratio**: Motor to wheel ratio (typically 3.5-6.0)
- **Load per Car**: Weight in kg (typically 8000-15000kg)
- **Passenger Weight**: Average per passenger in kg (typically 68-75kg)

Click "Update Parameters" to save changes.

### 2. Running Simulations

**Simulation Control Tab:**
- Choose simulation type:
  - **Dynamic**: Full physics simulation with acceleration/deceleration
  - **Static**: Steady-state analysis
- Click "Start Simulation" to begin
- Monitor progress in the status area

### 3. Viewing Results

**Results Tab:**
- **Speed Profile**: Shows speed over time
- **Power Profile**: Shows power consumption over time
- **Energy Consumption**: Cumulative energy usage
- **Summary Statistics**: Key performance metrics

**Export Options:**
- Click "Export Data" to save results as JSON
- Use browser print function for charts

## Tips and Best Practices

### Parameter Guidelines

**For Urban Transit:**
- Wheel diameter: 860mm
- Gear ratio: 4.5-5.0
- Load per car: 10000-12000kg

**For High-Speed Rail:**
- Wheel diameter: 1040mm
- Gear ratio: 3.5-4.0
- Load per car: 12000-15000kg

### Performance Optimization

- Close other applications during long simulations
- Use "Static" mode for quick parameter studies
- Export results regularly to avoid data loss

### Troubleshooting

**App Won't Start:**
- Check system requirements
- Run as administrator (Windows)
- Check firewall settings

**Simulation Fails:**
- Verify all parameters are realistic values
- Check backend status indicator
- Restart the application

**Charts Not Displaying:**
- Ensure simulation completed successfully
- Refresh the Results tab
- Check browser console for errors

## Keyboard Shortcuts

- `Ctrl+1`: Parameters tab
- `Ctrl+2`: Simulation tab
- `Ctrl+3`: Results tab
- `Ctrl+R`: Refresh backend connection
- `Ctrl+E`: Export results
- `F5`: Reload application

## Support

For technical support:
1. Check the troubleshooting section
2. Review application logs
3. Contact support with error details

## Advanced Features

### Custom Simulation Types

Advanced users can modify simulation parameters by editing the configuration files or using the API directly.

### Batch Processing

For multiple simulations, consider using the HTTP API directly:

```bash
# Update parameters
curl -X POST http://localhost:8080/api/parameters/train \
  -H "Content-Type: application/json" \
  -d '{"tractionMotors": 4, "axles": 8}'

# Start simulation
curl -X POST http://localhost:8080/api/simulation/start

# Get results
curl http://localhost:8080/api/simulation/results
```
```

#### Afternoon: Final Testing Checklist
Create `scripts/final-test.sh`:

```bash
#!/bin/bash

echo "🧪 Running final integration tests..."

# Test 1: Build system
echo ""
echo "1. Testing build system..."
./scripts/build-dev.sh
if [ $? -eq 0 ]; then
    echo "✅ Development build successful"
else
    echo "❌ Development build failed"
    exit 1
fi

# Test 2: Backend functionality
echo ""
echo "2. Testing backend..."
./scripts/test-integration.sh
if [ $? -eq 0 ]; then
    echo "✅ Backend tests passed"
else
    echo "❌ Backend tests failed"
    exit 1
fi

# Test 3: Frontend dependencies
echo ""
echo "3. Testing frontend..."
cd frontend
npm run build
if [ $? -eq 0 ]; then
    echo "✅ Frontend build successful"
else
    echo "❌ Frontend build failed"
    exit 1
fi
cd ..

# Test 4: Production build
echo ""
echo "4. Testing production build..."
./scripts/build-production.sh
if [ $? -eq 0 ]; then
    echo "✅ Production build successful"
else
    echo "❌ Production build failed"
    exit 1
fi

echo ""
echo "🎉 All tests passed! Application is ready for deployment."
echo ""
echo "📁 Distribution packages:"
find frontend/dist -type f \( -name "*.AppImage" -o -name "*.deb" -o -name "*.rpm" \) 2>/dev/null || echo "No packages found"

echo ""
echo "✅ Final checklist:"
echo "  - ✅ Backend builds and responds to API calls"
echo "  - ✅ Frontend builds and connects to backend"
echo "  - ✅ Electron packages the application"
echo "  - ✅ Production build creates distribution packages"
echo "  - ✅ Documentation is complete"
```

#### Evening: Create Release Package
```bash
# Make final test script executable
chmod +x scripts/final-test.sh

# Run final tests
./scripts/final-test.sh

# Create release documentation
echo "Creating release package..."
mkdir -p release
cp README.md release/
cp USER_MANUAL.md release/
cp -r frontend/dist/* release/ 2>/dev/null || echo "No dist files yet"

echo "✅ Release package ready in ./release/"
```

**✅ Day 10 Goal**: Complete application with documentation, testing, and production builds ready

---

## 📋 Final Implementation Checklist

### ✅ Complete Setup Verification

**Day 4**: Basic Electron Integration
- [ ] Electron launches Next.js content
- [ ] Qt backend starts from Electron
- [ ] Basic window and process management works

**Day 5**: Backend Connection Testing  
- [ ] API service can connect to Qt backend
- [ ] Health check endpoint responds
- [ ] Parameter update test works
- [ ] Error handling for connection failures

**Day 6**: UI Development
- [ ] Parameter input forms functional
- [ ] Simulation control interface works
- [ ] Tabbed navigation implemented
- [ ] Basic styling with Tailwind/shadcn

**Day 7**: Results Visualization
- [ ] Chart components display data
- [ ] Mock data shows properly
- [ ] Export functionality works
- [ ] Summary statistics displayed

**Day 8**: Build System
- [ ] Development scripts work
- [ ] Production build completes
- [ ] Cross-platform considerations handled
- [ ] Electron packaging successful

**Day 9**: Testing & Error Handling
- [ ] Integration tests pass
- [ ] Error boundaries catch issues
- [ ] Health monitoring works
- [ ] Connection retry mechanisms

**Day 10**: Final Polish
- [ ] Documentation complete
- [ ] User manual written
- [ ] Final testing passes
- [ ] Distribution packages created

### 🚀 Ready for Production

Your transformed Train Simulation App is now ready with:
- Modern React/Next.js frontend
- Headless Qt backend with HTTP API
- Cross-platform Electron desktop wrapper
- Professional build and deployment process

**Next Steps:**
1. Run `./scripts/build-dev.sh` to setup development
2. Test with `./scripts/start-dev.sh`
3. Build production version with `./scripts/build-production.sh`
4. Distribute the packages from `frontend/dist/`

This approach gives you a modern, maintainable desktop application while preserving your existing Qt simulation logic!

---



<!-- ### 🗓️ Day 4: Initialize Next.js Frontend

#### Morning: Create Next.js Project
```bash
# Navigate to frontend directory
cd train-simulation-desktop/frontend

# Initialize Next.js with TypeScript and Tailwind
npx create-next-app@latest . --typescript --tailwind --eslint --app --src-dir

# Install additional dependencies
npm install axios @tanstack/react-query recharts lucide-react
npm install @radix-ui/react-dialog @radix-ui/react-select @radix-ui/react-toast
npm install class-variance-authority clsx tailwind-merge

# Install Electron dependencies
npm install --save-dev electron electron-builder concurrently wait-on cross-env
npm install --save-dev @types/electron
```

#### Afternoon: Setup Project Structure
```bash
# Create additional directories
mkdir -p src/{components,services,hooks,types,utils}
mkdir -p src/components/{ui,forms,charts,layout}
mkdir -p electron
```

#### Create Basic API Service
Create `train-simulation-desktop/frontend/src/services/api.ts`:

```typescript
import axios, { AxiosInstance } from 'axios';

const API_BASE_URL = 'http://localhost:8080';

export interface TrainParameters {
  tractionMotors: number;
  axles: number;
  wheelDiameter: number;
  gearRatio: number;
  loadPerCar: number;
  passengerWeight: number;
}

export interface ElectricalParameters {
  voltage: number;
  frequency: number;
  powerFactor: number;
}

export interface SimulationResults {
  speedProfile: number[];
  timeProfile: number[];
  powerProfile: number[];
  energyConsumption: number;
}

class TrainSimulationAPI {
  private client: AxiosInstance;

  constructor() {
    this.client = axios.create({
      baseURL: API_BASE_URL,
      timeout: 10000,
      headers: {
        'Content-Type': 'application/json',
      },
    });
  }

  // Health check
  async checkHealth(): Promise<{ status: string; message: string }> {
    const response = await this.client.get('/api/health');
    return response.data;
  }

  // Parameters
  async updateTrainParameters(params: TrainParameters): Promise<any> {
    const response = await this.client.post('/api/parameters/train', params);
    return response.data;
  }

  async updateElectricalParameters(params: ElectricalParameters): Promise<any> {
    const response = await this.client.post('/api/parameters/electrical', params);
    return response.data;
  }

  // Simulation
  async startSimulation(type: 'dynamic' | 'static' = 'dynamic'): Promise<any> {
    const response = await this.client.post('/api/simulation/start', { type });
    return response.data;
  }

  async getSimulationResults(): Promise<SimulationResults> {
    const response = await this.client.get('/api/simulation/results');
    return response.data.results;
  }
}

export const api = new TrainSimulationAPI();
```

#### Evening: Create Basic UI Components
Create `train-simulation-desktop/frontend/src/components/ui/button.tsx`:

```tsx
import * as React from "react"
import { Slot } from "@radix-ui/react-slot"
import { cva, type VariantProps } from "class-variance-authority"
import { cn } from "@/lib/utils"

const buttonVariants = cva(
  "inline-flex items-center justify-center whitespace-nowrap rounded-md text-sm font-medium transition-colors focus-visible:outline-none focus-visible:ring-1 focus-visible:ring-ring disabled:pointer-events-none disabled:opacity-50",
  {
    variants: {
      variant: {
        default: "bg-primary text-primary-foreground shadow hover:bg-primary/90",
        destructive: "bg-destructive text-destructive-foreground shadow-sm hover:bg-destructive/90",
        outline: "border border-input bg-background shadow-sm hover:bg-accent hover:text-accent-foreground",
        secondary: "bg-secondary text-secondary-foreground shadow-sm hover:bg-secondary/80",
        ghost: "hover:bg-accent hover:text-accent-foreground",
        link: "text-primary underline-offset-4 hover:underline",
      },
      size: {
        default: "h-9 px-4 py-2",
        sm: "h-8 rounded-md px-3 text-xs",
        lg: "h-10 rounded-md px-8",
        icon: "h-9 w-9",
      },
    },
    defaultVariants: {
      variant: "default",
      size: "default",
    },
  }
)

export interface ButtonProps
  extends React.ButtonHTMLAttributes<HTMLButtonElement>,
    VariantProps<typeof buttonVariants> {
  asChild?: boolean
}

const Button = React.forwardRef<HTMLButtonElement, ButtonProps>(
  ({ className, variant, size, asChild = false, ...props }, ref) => {
    const Comp = asChild ? Slot : "button"
    return (
      <Comp
        className={cn(buttonVariants({ variant, size, className }))}
        ref={ref}
        {...props}
      />
    )
  }
)
Button.displayName = "Button"

export { Button, buttonVariants }
```

**✅ Day 4 Goal**: Next.js project initialized with basic structure and API service

---

### 🗓️ Day 5: Create React Components and Forms

#### Morning: Create Parameter Forms
Create `train-simulation-desktop/frontend/src/components/forms/TrainParameterForm.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { useMutation, useQueryClient } from '@tanstack/react-query';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { api, TrainParameters } from '@/services/api';
import { toast } from '@/components/ui/use-toast';

export default function TrainParameterForm() {
  const [parameters, setParameters] = useState<TrainParameters>({
    tractionMotors: 4,
    axles: 8,
    wheelDiameter: 860,
    gearRatio: 7.07,
    loadPerCar: 10,
    passengerWeight: 68,
  });

  const queryClient = useQueryClient();

  const updateMutation = useMutation({
    mutationFn: (params: TrainParameters) => api.updateTrainParameters(params),
    onSuccess: () => {
      toast({
        title: "Success",
        description: "Train parameters updated successfully",
      });
      queryClient.invalidateQueries({ queryKey: ['parameters'] });
    },
    onError: (error) => {
      toast({
        title: "Error",
        description: "Failed to update parameters",
        variant: "destructive",
      });
    },
  });

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    updateMutation.mutate(parameters);
  };

  const handleInputChange = (field: keyof TrainParameters, value: string) => {
    setParameters(prev => ({
      ...prev,
      [field]: parseFloat(value) || 0
    }));
  };

  return (
    <Card className="w-full max-w-2xl">
      <CardHeader>
        <CardTitle>Train Parameters</CardTitle>
      </CardHeader>
      <CardContent>
        <form onSubmit={handleSubmit} className="space-y-4">
          <div className="grid grid-cols-2 gap-4">
            <div className="space-y-2">
              <Label htmlFor="tractionMotors">Traction Motors</Label>
              <Input
                id="tractionMotors"
                type="number"
                value={parameters.tractionMotors}
                onChange={(e) => handleInputChange('tractionMotors', e.target.value)}
              />
            </div>
            
            <div className="space-y-2">
              <Label htmlFor="axles">Number of Axles</Label>
              <Input
                id="axles"
                type="number"
                value={parameters.axles}
                onChange={(e) => handleInputChange('axles', e.target.value)}
              />
            </div>
            
            <div className="space-y-2">
              <Label htmlFor="wheelDiameter">Wheel Diameter (mm)</Label>
              <Input
                id="wheelDiameter"
                type="number"
                value={parameters.wheelDiameter}
                onChange={(e) => handleInputChange('wheelDiameter', e.target.value)}
              />
            </div>
            
            <div className="space-y-2">
              <Label htmlFor="gearRatio">Gear Ratio</Label>
              <Input
                id="gearRatio"
                type="number"
                step="0.01"
                value={parameters.gearRatio}
                onChange={(e) => handleInputChange('gearRatio', e.target.value)}
              />
            </div>
            
            <div className="space-y-2">
              <Label htmlFor="loadPerCar">Load per Car (tons)</Label>
              <Input
                id="loadPerCar"
                type="number"
                value={parameters.loadPerCar}
                onChange={(e) => handleInputChange('loadPerCar', e.target.value)}
              />
            </div>
            
            <div className="space-y-2">
              <Label htmlFor="passengerWeight">Passenger Weight (kg)</Label>
              <Input
                id="passengerWeight"
                type="number"
                value={parameters.passengerWeight}
                onChange={(e) => handleInputChange('passengerWeight', e.target.value)}
              />
            </div>
          </div>
          
          <Button 
            type="submit" 
            disabled={updateMutation.isPending} 
            className="w-full"
          >
            {updateMutation.isPending ? 'Updating...' : 'Update Parameters'}
          </Button>
        </form>
      </CardContent>
    </Card>
  );
}
```

#### Afternoon: Create Simulation Control Component
Create `train-simulation-desktop/frontend/src/components/forms/SimulationControl.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { useMutation, useQuery } from '@tanstack/react-query';
import { Button } from '@/components/ui/button';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Select, SelectContent, SelectItem, SelectTrigger, SelectValue } from '@/components/ui/select';
import { api } from '@/services/api';
import { toast } from '@/components/ui/use-toast';
import { Play, Square } from 'lucide-react';

export default function SimulationControl() {
  const [simulationType, setSimulationType] = useState<'dynamic' | 'static'>('dynamic');

  const simulationMutation = useMutation({
    mutationFn: (type: 'dynamic' | 'static') => api.startSimulation(type),
    onSuccess: () => {
      toast({
        title: "Simulation Started",
        description: "The simulation is now running...",
      });
    },
    onError: (error) => {
      toast({
        title: "Simulation Failed",
        description: "Failed to start simulation",
        variant: "destructive",
      });
    },
  });

  const { data: health, isLoading } = useQuery({
    queryKey: ['health'],
    queryFn: () => api.checkHealth(),
    refetchInterval: 5000,
  });

  const handleStartSimulation = () => {
    simulationMutation.mutate(simulationType);
  };

  return (
    <Card className="w-full max-w-md">
      <CardHeader>
        <CardTitle>Simulation Control</CardTitle>
      </CardHeader>
      <CardContent className="space-y-4">
        <div className="space-y-2">
          <label className="text-sm font-medium">Simulation Type</label>
          <Select value={simulationType} onValueChange={(value: 'dynamic' | 'static') => setSimulationType(value)}>
            <SelectTrigger>
              <SelectValue />
            </SelectTrigger>
            <SelectContent>
              <SelectItem value="dynamic">Dynamic Analysis</SelectItem>
              <SelectItem value="static">Static Analysis</SelectItem>
            </SelectContent>
          </Select>
        </div>

        <div className="flex items-center space-x-2 text-sm">
          <div className={`w-3 h-3 rounded-full ${health?.status === 'ok' ? 'bg-green-500' : 'bg-red-500'}`} />
          <span>Backend: {isLoading ? 'Checking...' : health?.status === 'ok' ? 'Connected' : 'Disconnected'}</span>
        </div>

        <Button
          onClick={handleStartSimulation}
          disabled={simulationMutation.isPending || health?.status !== 'ok'}
          className="w-full"
        >
          <Play className="w-4 h-4 mr-2" />
          {simulationMutation.isPending ? 'Running...' : 'Start Simulation'}
        </Button>
      </CardContent>
    </Card>
  );
}
```

#### Evening: Create Main Layout
Create `train-simulation-desktop/frontend/src/components/layout/AppLayout.tsx`:

```tsx
'use client';

import { QueryClient, QueryClientProvider } from '@tanstack/react-query';
import { Toaster } from '@/components/ui/toaster';
import { useState } from 'react';

export default function AppLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  const [queryClient] = useState(() => new QueryClient());

  return (
    <QueryClientProvider client={queryClient}>
      <div className="min-h-screen bg-gray-50">
        <header className="bg-white shadow-sm border-b">
          <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
            <div className="flex justify-between h-16">
              <div className="flex items-center">
                <h1 className="text-xl font-semibold text-gray-900">
                  Train Simulation App
                </h1>
              </div>
            </div>
          </div>
        </header>
        
        <main className="max-w-7xl mx-auto py-6 sm:px-6 lg:px-8">
          {children}
        </main>
      </div>
      <Toaster />
    </QueryClientProvider>
  );
}
```

**✅ Day 5 Goal**: React components created for parameter input and simulation control

---

### 🗓️ Day 6: Setup Electron Integration

#### Morning: Configure Electron
Create `train-simulation-desktop/frontend/electron/main.js`:

```javascript
const { app, BrowserWindow, ipcMain } = require('electron');
const { spawn } = require('child_process');
const path = require('path');
const isDev = require('electron-is-dev');
const axios = require('axios');

let mainWindow;
let qtBackendProcess;

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1400,
    height: 900,
    webPreferences: {
      nodeIntegration: false,
      contextIsolation: true,
      preload: path.join(__dirname, 'preload.js'),
    },
    icon: path.join(__dirname, '../public/icon.png'), // Add your app icon
    show: false, // Don't show until ready
  });

  const startUrl = isDev 
    ? 'http://localhost:3000' 
    : `file://${path.join(__dirname, '../out/index.html')}`;
  
  mainWindow.loadURL(startUrl);

  mainWindow.once('ready-to-show', () => {
    mainWindow.show();
  });

  if (isDev) {
    mainWindow.webContents.openDevTools();
  }

  mainWindow.on('closed', () => {
    mainWindow = null;
  });
}

async function startQtBackend() {
  const isWindows = process.platform === 'win32';
  const executableName = isWindows ? 'TrainSimulationApp.exe' : 'TrainSimulationApp';
  
  const backendPath = isDev 
    ? path.join(__dirname, '../../backend/build', executableName)
    : path.join(process.resourcesPath, 'backend', executableName);
  
  // Make executable on Linux/Mac
  if (!isWindows && isDev) {
    try {
      require('fs').chmodSync(backendPath, '755');
    } catch (error) {
      console.error('Failed to make backend executable:', error);
    }
  }
  
  console.log('Starting Qt backend from:', backendPath);
  
  qtBackendProcess = spawn(backendPath, ['--server', '--port', '8080'], {
    stdio: ['pipe', 'pipe', 'pipe'],
  });

  qtBackendProcess.stdout.on('data', (data) => {
    console.log(`Qt Backend: ${data}`);
  });

  qtBackendProcess.stderr.on('data', (data) => {
    console.error(`Qt Backend Error: ${data}`);
  });

  qtBackendProcess.on('close', (code) => {
    console.log(`Qt Backend exited with code ${code}`);
  });

  // Wait for backend to be ready
  await waitForBackend();
}

async function waitForBackend(maxAttempts = 30) {
  for (let i = 0; i < maxAttempts; i++) {
    try {
      await axios.get('http://localhost:8080/api/health', { timeout: 1000 });
      console.log('✅ Qt Backend is ready');
      return true;
    } catch (error) {
      console.log(`Waiting for backend... (${i + 1}/${maxAttempts})`);
      await new Promise(resolve => setTimeout(resolve, 1000));
    }
  }
  throw new Error('Backend failed to start within timeout');
}

// IPC Handlers
ipcMain.handle('check-backend-health', async () => {
  try {
    const response = await axios.get('http://localhost:8080/api/health');
    return { success: true, data: response.data };
  } catch (error) {
    return { success: false, error: error.message };
  }
});

ipcMain.handle('restart-backend', async () => {
  if (qtBackendProcess) {
    qtBackendProcess.kill();
  }
  
  try {
    await startQtBackend();
    return { success: true };
  } catch (error) {
    return { success: false, error: error.message };
  }
});

// App Event Handlers
app.whenReady().then(async () => {
  try {
    await startQtBackend();
    createWindow();
  } catch (error) {
    console.error('Failed to start application:', error);
    app.quit();
  }
});

app.on('window-all-closed', () => {
  if (qtBackendProcess) {
    qtBackendProcess.kill();
  }
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('before-quit', () => {
  if (qtBackendProcess) {
    qtBackendProcess.kill();
  }
});

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow();
  }
});
```

#### Afternoon: Create Preload Script
Create `train-simulation-desktop/frontend/electron/preload.js`:

```javascript
const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('electronAPI', {
  // Backend management
  checkBackendHealth: () => ipcRenderer.invoke('check-backend-health'),
  restartBackend: () => ipcRenderer.invoke('restart-backend'),
  
  // Platform info
  platform: process.platform,
  
  // App info
  getVersion: () => process.env.npm_package_version || '1.0.0',
});
```

#### Evening: Update Package.json Scripts
Update `train-simulation-desktop/frontend/package.json`:

```json
{
  "name": "train-simulation-frontend",
  "version": "1.0.0",
  "main": "electron/main.js",
  "homepage": "./",
  "scripts": {
    "dev": "next dev",
    "build": "next build",
    "start": "next start",
    "lint": "next lint",
    "electron": "electron .",
    "electron-dev": "concurrently \"npm run dev\" \"wait-on http://localhost:3000 && electron .\"",
    "electron-pack": "npm run build && electron-builder",
    "preelectron-pack": "npm run build"
  },
  "build": {
    "appId": "com.trainSimulation.app",
    "productName": "Train Simulation App",
    "directories": {
      "output": "dist"
    },
    "files": [
      "out/**/*",
      "electron/**/*",
      "node_modules/**/*"
    ],
    "extraResources": [
      {
        "from": "../backend/build/",
        "to": "backend/",
        "filter": ["**/*"]
      }
    ],
    "linux": {
      "target": "AppImage",
      "category": "Engineering"
    },
    "win": {
      "target": "nsis"
    }
  }
}
```

**✅ Day 6 Goal**: Electron configured to launch Qt backend and Next.js frontend

---

### 🗓️ Day 7: Create Main Application Page

#### Morning: Update Next.js App
Update `train-simulation-desktop/frontend/src/app/page.tsx`:

```tsx
'use client';

import { useState } from 'react';
import { useQuery } from '@tanstack/react-query';
import AppLayout from '@/components/layout/AppLayout';
import TrainParameterForm from '@/components/forms/TrainParameterForm';
import SimulationControl from '@/components/forms/SimulationControl';
import SimulationResults from '@/components/charts/SimulationResults';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs';
import { api } from '@/services/api';

export default function Home() {
  const [activeTab, setActiveTab] = useState('parameters');

  const { data: health } = useQuery({
    queryKey: ['health'],
    queryFn: () => api.checkHealth(),
    refetchInterval: 5000,
  });

  return (
    <AppLayout>
      <div className="space-y-6">
        {/* Header */}
        <div className="bg-white rounded-lg shadow p-6">
          <div className="flex items-center justify-between">
            <div>
              <h1 className="text-2xl font-bold text-gray-900">
                Train Simulation Desktop
              </h1>
              <p className="text-gray-600">
                Advanced train performance analysis and simulation
              </p>
            </div>
            <div className="flex items-center space-x-2">
              <div className={`w-3 h-3 rounded-full ${
                health?.status === 'ok' ? 'bg-green-500' : 'bg-red-500'
              }`} />
              <span className="text-sm text-gray-600">
                Backend {health?.status === 'ok' ? 'Connected' : 'Disconnected'}
              </span>
            </div>
          </div>
        </div>

        {/* Main Content */}
        <Tabs value={activeTab} onValueChange={setActiveTab} className="w-full">
          <TabsList className="grid w-full grid-cols-4">
            <TabsTrigger value="parameters">Parameters</TabsTrigger>
            <TabsTrigger value="simulation">Simulation</TabsTrigger>
            <TabsTrigger value="results">Results</TabsTrigger>
            <TabsTrigger value="settings">Settings</TabsTrigger>
          </TabsList>

          <TabsContent value="parameters" className="space-y-6">
            <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
              <TrainParameterForm />
              <Card>
                <CardHeader>
                  <CardTitle>Electrical Parameters</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-gray-600">
                    Electrical parameter form will be added here
                  </p>
                </CardContent>
              </Card>
            </div>
          </TabsContent>

          <TabsContent value="simulation" className="space-y-6">
            <div className="grid grid-cols-1 lg:grid-cols-3 gap-6">
              <SimulationControl />
              <Card className="lg:col-span-2">
                <CardHeader>
                  <CardTitle>Simulation Progress</CardTitle>
                </CardHeader>
                <CardContent>
                  <p className="text-gray-600">
                    Simulation progress and status will be shown here
                  </p>
                </CardContent>
              </Card>
            </div>
          </TabsContent>

          <TabsContent value="results" className="space-y-6">
            <SimulationResults />
          </TabsContent>

          <TabsContent value="settings" className="space-y-6">
            <Card>
              <CardHeader>
                <CardTitle>Application Settings</CardTitle>
              </CardHeader>
              <CardContent>
                <p className="text-gray-600">
                  Settings and preferences will be added here
                </p>
              </CardContent>
            </Card>
          </TabsContent>
        </Tabs>
      </div>
    </AppLayout>
  );
}
```

#### Afternoon: Create Results Visualization
Create `train-simulation-desktop/frontend/src/components/charts/SimulationResults.tsx`:

```tsx
'use client';

import { useQuery } from '@tanstack/react-query';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';
import { api } from '@/services/api';
import { Button } from '@/components/ui/button';
import { RefreshCw, Download } from 'lucide-react';

export default function SimulationResults() {
  const { data: results, isLoading, refetch } = useQuery({
    queryKey: ['simulation-results'],
    queryFn: () => api.getSimulationResults(),
    enabled: false, // Only fetch when explicitly requested
  });

  // Transform data for charts
  const chartData = results ? results.speedProfile.map((speed, index) => ({
    time: results.timeProfile[index] || index,
    speed: speed,
    power: results.powerProfile[index] || 0,
  })) : [];

  const handleRefresh = () => {
    refetch();
  };

  const handleExport = () => {
    if (results) {
      const dataStr = JSON.stringify(results, null, 2);
      const dataBlob = new Blob([dataStr], { type: 'application/json' });
      const url = URL.createObjectURL(dataBlob);
      const link = document.createElement('a');
      link.href = url;
      link.download = 'simulation-results.json';
      link.click();
    }
  };

  return (
    <div className="space-y-6">
      {/* Controls */}
      <Card>
        <CardHeader>
          <div className="flex items-center justify-between">
            <CardTitle>Simulation Results</CardTitle>
            <div className="flex space-x-2">
              <Button onClick={handleRefresh} disabled={isLoading} variant="outline" size="sm">
                <RefreshCw className="w-4 h-4 mr-2" />
                Refresh
              </Button>
              <Button onClick={handleExport} disabled={!results} variant="outline" size="sm">
                <Download className="w-4 h-4 mr-2" />
                Export
              </Button>
            </div>
          </div>
        </CardHeader>
      </Card>

      {/* Charts */}
      {isLoading ? (
        <Card>
          <CardContent className="p-6">
            <div className="flex items-center justify-center h-64">
              <div className="text-center">
                <RefreshCw className="w-8 h-8 animate-spin mx-auto mb-2" />
                <p>Loading results...</p>
              </div>
            </div>
          </CardContent>
        </Card>
      ) : results && chartData.length > 0 ? (
        <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
          {/* Speed Profile */}
          <Card>
            <CardHeader>
              <CardTitle>Speed Profile</CardTitle>
            </CardHeader>
            <CardContent>
              <ResponsiveContainer width="100%" height={300}>
                <LineChart data={chartData}>
                  <CartesianGrid strokeDasharray="3 3" />
                  <XAxis dataKey="time" label={{ value: 'Time (s)', position: 'insideBottom', offset: -10 }} />
                  <YAxis label={{ value: 'Speed (km/h)', angle: -90, position: 'insideLeft' }} />
                  <Tooltip />
                  <Legend />
                  <Line type="monotone" dataKey="speed" stroke="#8884d8" strokeWidth={2} />
                </LineChart>
              </ResponsiveContainer>
            </CardContent>
          </Card>

          {/* Power Profile */}
          <Card>
            <CardHeader>
              <CardTitle>Power Profile</CardTitle>
            </CardHeader>
            <CardContent>
              <ResponsiveContainer width="100%" height={300}>
                <LineChart data={chartData}>
                  <CartesianGrid strokeDasharray="3 3" />
                  <XAxis dataKey="time" label={{ value: 'Time (s)', position: 'insideBottom', offset: -10 }} />
                  <YAxis label={{ value: 'Power (kW)', angle: -90, position: 'insideLeft' }} />
                  <Tooltip />
                  <Legend />
                  <Line type="monotone" dataKey="power" stroke="#82ca9d" strokeWidth={2} />
                </LineChart>
              </ResponsiveContainer>
            </CardContent>
          </Card>
        </div>
      ) : (
        <Card>
          <CardContent className="p-6">
            <div className="text-center text-gray-500">
              <p>No simulation results available</p>
              <p className="text-sm">Run a simulation to see results here</p>
            </div>
          </CardContent>
        </Card>
      )}

      {/* Summary Statistics */}
      {results && (
        <Card>
          <CardHeader>
            <CardTitle>Summary</CardTitle>
          </CardHeader>
          <CardContent>
            <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
              <div className="text-center">
                <div className="text-2xl font-bold text-blue-600">
                  {Math.max(...results.speedProfile).toFixed(1)}
                </div>
                <div className="text-sm text-gray-600">Max Speed (km/h)</div>
              </div>
              <div className="text-center">
                <div className="text-2xl font-bold text-green-600">
                  {Math.max(...results.powerProfile).toFixed(1)}
                </div>
                <div className="text-sm text-gray-600">Max Power (kW)</div>
              </div>
              <div className="text-center">
                <div className="text-2xl font-bold text-orange-600">
                  {results.energyConsumption?.toFixed(2) || 'N/A'}
                </div>
                <div className="text-sm text-gray-600">Energy (kWh)</div>
              </div>
              <div className="text-center">
                <div className="text-2xl font-bold text-purple-600">
                  {Math.max(...results.timeProfile).toFixed(1)}
                </div>
                <div className="text-sm text-gray-600">Total Time (s)</div>
              </div>
            </div>
          </CardContent>
        </Card>
      )}
    </div>
  );
}
```

**✅ Day 7 Goal**: Complete Next.js application with tabbed interface and charts

---

### 🗓️ Day 8: Build Scripts and Testing

#### Morning: Create Build Scripts
Create `train-simulation-desktop/scripts/build-all.sh`:

```bash
#!/bin/bash
set -e

echo "🚀 Building Train Simulation Desktop App (Linux)..."

# Build Qt Backend
echo ""
echo "📦 [1/3] Building Qt Backend..."
cd backend
mkdir -p build
cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Verify backend executable
if [ -f "TrainSimulationApp" ]; then
    echo "✅ Qt Backend built successfully"
    chmod +x TrainSimulationApp
else
    echo "❌ Qt Backend build failed"
    exit 1
fi

cd ../..

# Build Frontend
echo ""
echo "🌐 [2/3] Building Next.js Frontend..."
cd frontend

# Install dependencies if needed
if [ ! -d "node_modules" ]; then
    echo "Installing npm dependencies..."
    npm install
fi

# Build Next.js app
npm run build

# Check if build succeeded
if [ -d "out" ] || [ -d ".next" ]; then
    echo "✅ Frontend built successfully"
else
    echo "❌ Frontend build failed"
    exit 1
fi

cd ..

# Package Electron App
echo ""
echo "📱 [3/3] Packaging Electron App..."
cd frontend

# Install electron dependencies if needed
npm install electron electron-builder --save-dev

# Build the app
npm run electron-pack

if [ -d "dist" ]; then
    echo "✅ Electron app packaged successfully"
    echo ""
    echo "📁 Build artifacts located in:"
    echo "   - Backend: backend/build/"
    echo "   - Frontend: frontend/out/"
    echo "   - Package: frontend/dist/"
    echo ""
    ls -la dist/
else
    echo "❌ Electron packaging failed"
    exit 1
fi

cd ..

echo ""
echo "🎉 Build complete! Your app is ready for distribution."
```

#### Afternoon: Create Development Scripts
Create `train-simulation-desktop/scripts/dev-setup.sh`:

```bash
#!/bin/bash
set -e

echo "🔧 Setting up development environment..."

# Check prerequisites
echo "Checking prerequisites..."

# Node.js
if ! command -v node &> /dev/null; then
    echo "❌ Node.js not found. Please install Node.js 18+"
    exit 1
fi

# Qt
if ! command -v qmake &> /dev/null && ! command -v cmake &> /dev/null; then
    echo "❌ Qt development tools not found"
    echo "Please install: sudo dnf install qt6-qtbase-devel cmake"
    exit 1
fi

echo "✅ Prerequisites check passed"

# Setup backend
echo ""
echo "🏗️ Setting up Qt Backend..."
cd backend
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
cd ../..

# Setup frontend
echo ""
echo "🌐 Setting up Next.js Frontend..."
cd frontend

# Install dependencies
npm install

# Install additional Electron dependencies
npm install --save-dev electron electron-builder concurrently wait-on cross-env

cd ..

echo ""
echo "✅ Development environment setup complete!"
echo ""
echo "🚀 To start development:"
echo "   1. Terminal 1: cd backend/build && ./TrainSimulationApp --server"
echo "   2. Terminal 2: cd frontend && npm run electron-dev"
echo ""
echo "📖 Or run: ./scripts/start-dev.sh"
```

Create `train-simulation-desktop/scripts/start-dev.sh`:

```bash
#!/bin/bash

echo "🚀 Starting Train Simulation App in development mode..."

# Function to kill background processes
cleanup() {
    echo ""
    echo "🛑 Shutting down..."
    if [ ! -z "$BACKEND_PID" ]; then
        kill $BACKEND_PID 2>/dev/null
    fi
    if [ ! -z "$FRONTEND_PID" ]; then
        kill $FRONTEND_PID 2>/dev/null
    fi
    exit 0
}

# Trap Ctrl+C
trap cleanup SIGINT

# Start Qt Backend
echo "📦 Starting Qt Backend..."
cd backend/build
./TrainSimulationApp --server &
BACKEND_PID=$!
cd ../..

# Wait a moment for backend to start
sleep 3

# Start Frontend
echo "🌐 Starting Frontend..."
cd frontend
npm run electron-dev &
FRONTEND_PID=$!
cd ..

echo ""
echo "✅ Both backend and frontend are starting..."
echo "🌐 Frontend will open automatically when ready"
echo "🔍 Backend API available at: http://localhost:8080/api/health"
echo ""
echo "Press Ctrl+C to stop both services"

# Wait for user to stop
wait
```

#### Evening: Test the Complete Setup
```bash
# Make scripts executable
chmod +x scripts/*.sh

# Setup development environment
./scripts/dev-setup.sh

# Test development mode
./scripts/start-dev.sh
```

**Test checklist:**
- [ ] Qt backend starts and responds to `curl http://localhost:8080/api/health`
- [ ] Next.js frontend loads in Electron window
- [ ] Parameter forms can send data to backend
- [ ] Simulation can be triggered
- [ ] Results can be retrieved and displayed

**✅ Day 8 Goal**: Complete development and build scripts working

---

### 🗓️ Day 9: Integration Testing and Debugging

#### Morning: Create Integration Tests
Create `train-simulation-desktop/scripts/test-integration.sh`:

```bash
#!/bin/bash
set -e

echo "🧪 Running integration tests..."

# Start backend
echo "Starting backend for testing..."
cd backend/build
./TrainSimulationApp --server &
BACKEND_PID=$!
cd ../..

# Wait for backend to start
echo "Waiting for backend to start..."
sleep 5

# Test API endpoints
echo ""
echo "Testing API endpoints..."

# Test 1: Health check
echo "1. Testing health endpoint..."
HEALTH_RESPONSE=$(curl -s http://localhost:8080/api/health)
if echo "$HEALTH_RESPONSE" | grep -q "ok"; then
    echo "✅ Health check passed"
else
    echo "❌ Health check failed: $HEALTH_RESPONSE"
    kill $BACKEND_PID
    exit 1
fi

# Test 2: Parameter update
echo "2. Testing parameter update..."
PARAM_RESPONSE=$(curl -s -X POST http://localhost:8080/api/parameters/train \
    -H "Content-Type: application/json" \
    -d '{"tractionMotors": 4, "axles": 8, "wheelDiameter": 860}')

if echo "$PARAM_RESPONSE" | grep -q "success"; then
    echo "✅ Parameter update passed"
else
    echo "❌ Parameter update failed: $PARAM_RESPONSE"
fi

# Test 3: Simulation start
echo "3. Testing simulation start..."
SIM_RESPONSE=$(curl -s -X POST http://localhost:8080/api/simulation/start \
    -H "Content-Type: application/json" \
    -d '{"type": "dynamic"}')

if echo "$SIM_RESPONSE" | grep -q "success"; then
    echo "✅ Simulation start passed"
else
    echo "❌ Simulation start failed: $SIM_RESPONSE"
fi

# Test 4: Results retrieval
echo "4. Testing results retrieval..."
RESULTS_RESPONSE=$(curl -s http://localhost:8080/api/simulation/results)
if echo "$RESULTS_RESPONSE" | grep -q "results"; then
    echo "✅ Results retrieval passed"
else
    echo "⚠️  Results retrieval returned: $RESULTS_RESPONSE"
fi

# Cleanup
echo ""
echo "Stopping backend..."
kill $BACKEND_PID

echo ""
echo "🧪 Integration tests completed!"
```

#### Afternoon: Debug Common Issues
Create `train-simulation-desktop/scripts/debug-check.sh`:

```bash
#!/bin/bash

echo "🔍 Running debug checks..."

# Check Qt dependencies
echo ""
echo "1. Checking Qt dependencies..."
if [ -f "backend/build/TrainSimulationApp" ]; then
    echo "✅ Backend executable exists"
    
    # Check library dependencies
    echo "Library dependencies:"
    ldd backend/build/TrainSimulationApp | grep -E "(Qt6|libstdc++)" || echo "No Qt6 dependencies found"
else
    echo "❌ Backend executable not found"
    echo "Run: cd backend/build && cmake .. && make"
fi

# Check Node.js setup
echo ""
echo "2. Checking Node.js setup..."
cd frontend
if [ -f "package.json" ]; then
    echo "✅ Frontend package.json exists"
    
    # Check dependencies
    if [ -d "node_modules" ]; then
        echo "✅ Node modules installed"
    else
        echo "❌ Node modules missing. Run: npm install"
    fi
    
    # Check Electron
    if [ -f "node_modules/.bin/electron" ]; then
        echo "✅ Electron installed"
    else
        echo "❌ Electron missing. Run: npm install electron --save-dev"
    fi
else
    echo "❌ Frontend package.json not found"
fi
cd ..

# Check ports
echo ""
echo "3. Checking port availability..."
if netstat -tuln | grep -q ":8080 "; then
    echo "⚠️  Port 8080 is in use"
    echo "Processes using port 8080:"
    lsof -i :8080 || echo "Cannot determine which process is using port 8080"
else
    echo "✅ Port 8080 is available"
fi

if netstat -tuln | grep -q ":3000 "; then
    echo "⚠️  Port 3000 is in use"
else
    echo "✅ Port 3000 is available"
fi

# Check for common issues
echo ""
echo "4. Common issue checks..."

# Check if backend is actually executable
if [ -f "backend/build/TrainSimulationApp" ]; then
    if [ -x "backend/build/TrainSimulationApp" ]; then
        echo "✅ Backend has execute permissions"
    else
        echo "❌ Backend missing execute permissions. Run: chmod +x backend/build/TrainSimulationApp"
    fi
fi

# Check for missing libraries
echo ""
echo "5. System libraries check..."
MISSING_LIBS=()

if ! ldconfig -p | grep -q "libQt6Core"; then
    MISSING_LIBS+=("Qt6 Core")
fi

if ! ldconfig -p | grep -q "libQt6Network"; then
    MISSING_LIBS+=("Qt6 Network")
fi

if [ ${#MISSING_LIBS[@]} -eq 0 ]; then
    echo "✅ All required libraries found"
else
    echo "❌ Missing libraries: ${MISSING_LIBS[*]}"
    echo "Install with: sudo dnf install qt6-qtbase-devel qt6-qtnetworkauth-devel"
fi

echo ""
echo "🔍 Debug check completed!"
```

#### Evening: Create Troubleshooting Guide
Create `train-simulation-desktop/TROUBLESHOOTING.md`:

```markdown
# Troubleshooting Guide

## Common Issues and Solutions

### Backend Issues

#### Backend won't start
```bash
# Check if executable exists and has permissions
ls -la backend/build/TrainSimulationApp
chmod +x backend/build/TrainSimulationApp

# Check library dependencies
ldd backend/build/TrainSimulationApp

# Run with verbose output
./backend/build/TrainSimulationApp --server --verbose
```

#### Port 8080 already in use
```bash
# Find what's using the port
sudo lsof -i :8080

# Kill the process
sudo kill -9 [PID]

# Or use a different port
./backend/build/TrainSimulationApp --server --port 8081
```

### Frontend Issues

#### Electron won't start
```bash
# Check Node.js version
node --version  # Should be 18+

# Reinstall dependencies
rm -rf node_modules package-lock.json
npm install

# Check Electron installation
npm ls electron
```

#### Can't connect to backend
```bash
# Test backend manually
curl http://localhost:8080/api/health

# Check if backend is running
ps aux | grep TrainSimulationApp

# Check firewall (if any)
sudo ufw status
```

### Build Issues

#### CMake configuration fails
```bash
# Install Qt development packages
sudo dnf install qt6-qtbase-devel qt6-qtcharts-devel qt6-qtnetworkauth-devel

# Clear CMake cache
rm -rf backend/build
mkdir backend/build
cd backend/build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

#### npm install fails
```bash
# Clear npm cache
npm cache clean --force

# Use different registry if needed
npm install --registry https://registry.npmjs.org/

# Check Node.js version compatibility
node --version
npm --version
```

## Debugging Commands

```bash
# Run debug check script
./scripts/debug-check.sh

# Test integration
./scripts/test-integration.sh

# Check system resources
htop

# Monitor network connections
netstat -tuln | grep -E "(8080|3000)"

# Check Qt installation
qmake --version
```
```

**✅ Day 9 Goal**: Integration testing setup and troubleshooting tools ready

---

### 🗓️ Day 10: Final Polish and Deployment Prep

#### Morning: Add Error Handling and Loading States
Create `train-simulation-desktop/frontend/src/components/common/ErrorBoundary.tsx`:

```tsx
'use client';

import React from 'react';
import { Card, CardContent, CardHeader, CardTitle } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { AlertTriangle, RefreshCw } from 'lucide-react';

interface ErrorBoundaryState {
  hasError: boolean;
  error?: Error;
}

export class ErrorBoundary extends React.Component<
  React.PropsWithChildren<{}>,
  ErrorBoundaryState
> {
  constructor(props: React.PropsWithChildren<{}>) {
    super(props);
    this.state = { hasError: false };
  }

  static getDerivedStateFromError(error: Error): ErrorBoundaryState {
    return { hasError: true, error };
  }

  componentDidCatch(error: Error, errorInfo: React.ErrorInfo) {
    console.error('ErrorBoundary caught an error:', error, errorInfo);
  }

  render() {
    if (this.state.hasError) {
      return (
        <Card className="max-w-md mx-auto mt-8">
          <CardHeader>
            <CardTitle className="flex items-center text-red-600">
              <AlertTriangle className="w-5 h-5 mr-2" />
              Something went wrong
            </CardTitle>
          </CardHeader>
          <CardContent className="space-y-4">
            <p className="text-gray-600">
              The application encountered an unexpected error.
            </p>
            {this.state.error && (
              <details className="bg-gray-100 p-3 rounded text-sm">
                <summary className="cursor-pointer font-medium">
                  Error details
                </summary>
                <pre className="mt-2 whitespace-pre-wrap">
                  {this.state.error.message}
                </pre>
              </details>
            )}
            <Button
              onClick={() => window.location.reload()}
              className="w-full"
            >
              <RefreshCw className="w-4 h-4 mr-2" />
              Reload Application
            </Button>
          </CardContent>
        </Card>
      );
    }

    return this.props.children;
  }
}
```

#### Afternoon: Create Application Manifest and Icons
Create `train-simulation-desktop/frontend/public/manifest.json`:

```json
{
  "name": "Train Simulation App",
  "short_name": "TrainSim",
  "description": "Advanced train performance analysis and simulation tool",
  "version": "1.0.0",
  "author": "Your Name",
  "icons": [
    {
      "src": "icon-192.png",
      "sizes": "192x192",
      "type": "image/png"
    },
    {
      "src": "icon-512.png",
      "sizes": "512x512",
      "type": "image/png"
    }
  ]
}
```

Update Electron main process with proper app metadata:

```javascript
// In frontend/electron/main.js, add after app.whenReady():

app.setName('Train Simulation App');
app.setVersion('1.0.0');

// Set app user model ID for Windows
if (process.platform === 'win32') {
  app.setAppUserModelId('com.trainSimulation.app');
}
```

#### Evening: Final Production Build Test
Create `train-simulation-desktop/scripts/build-production.sh`:

```bash
#!/bin/bash
set -e

echo "🏭 Building for production..."

# Clean previous builds
echo "Cleaning previous builds..."
rm -rf backend/build
rm -rf frontend/out
rm -rf frontend/dist

# Build backend in release mode
echo ""
echo "📦 Building Qt Backend (Release)..."
cd backend
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3"
make -j$(nproc)

# Strip debug symbols to reduce size
strip TrainSimulationApp

echo "Backend size: $(du -h TrainSimulationApp | cut -f1)"
cd ../..

# Build frontend for production
echo ""
echo "🌐 Building Next.js Frontend (Production)..."
cd frontend

# Install dependencies
npm ci --production=false

# Build Next.js app
NODE_ENV=production npm run build

# Build Electron app
echo ""
echo "📱 Packaging Electron App..."
npm run electron-pack

# Show build results
echo ""
echo "🎉 Production build complete!"
echo ""
echo "📊 Build sizes:"
find dist -name "*.AppImage" -o -name "*.deb" -o -name "*.rpm" | while read file; do
    echo "  $(basename "$file"): $(du -h "$file" | cut -f1)"
done

cd ..

echo ""
echo "✅ Ready for distribution!"
echo "📁 Packages are in: frontend/dist/"
```

**Final Day 10 Tasks:**
1. Run complete build: `./scripts/build-production.sh`
2. Test the final package on a clean system
3. Create README.md with installation instructions
4. Test cross-platform builds (if Windows VM available)

**✅ Day 10 Goal**: Production-ready application with proper error handling and build process

---

## 📋 Daily Summary Checklist

### ✅ Day 1: Project Structure & Qt Backend Setup
- [ ] Project directories created
- [ ] CMakeLists.txt configured for headless build
- [ ] HTTP server class structure defined

### ✅ Day 2: Implement Qt HTTP Server  
- [ ] HTTP server implementation complete
- [ ] API routes defined
- [ ] Main.cpp modified for headless operation

### ✅ Day 3: Build and Test Qt Backend
- [ ] Qt backend builds successfully
- [ ] API endpoints respond correctly
- [ ] Integration with existing simulation logic

### ✅ Day 4: Initialize Next.js Frontend
- [ ] Next.js project created with TypeScript
- [ ] Dependencies installed
- [ ] API service layer implemented

### ✅ Day 5: Create React Components and Forms
- [ ] Parameter input forms created
- [ ] Simulation control component implemented
- [ ] Application layout designed

### ✅ Day 6: Setup Electron Integration
- [ ] Electron main process configured
- [ ] Qt backend lifecycle management
- [ ] IPC communication setup

### ✅ Day 7: Create Main Application Page
- [ ] Tabbed interface implemented
- [ ] Results visualization with charts
- [ ] Complete user interface functional

### ✅ Day 8: Build Scripts and Testing
- [ ] Cross-platform build scripts created
- [ ] Development environment setup scripts
- [ ] Basic integration testing

### ✅ Day 9: Integration Testing and Debugging
- [ ] Comprehensive test suite created
- [ ] Debug tools and troubleshooting guide
- [ ] Common issues identified and solved

### ✅ Day 10: Final Polish and Deployment Prep
- [ ] Error handling and loading states
- [ ] Application manifest and metadata
- [ ] Production build process tested

This 10-day guide transforms your Qt Train Simulation App into a modern desktop application with Next.js frontend and Electron wrapper!

```jsx
import { useState, useEffect } from 'react';
import { Card, CardHeader, CardTitle, CardContent } from '@/components/ui/card';
import { Button } from '@/components/ui/button';
import { Input } from '@/components/ui/input';
import { Label } from '@/components/ui/label';
import api from '@/services/api';

export default function TrainParameterForm() {
    const [parameters, setParameters] = useState({
        tractionMotors: 4,
        axles: 8,
        wheelDiameter: 860,
        gearRatio: 7.07,
        loadPerCar: 10,
        passengerWeight: 68
    });

    const [isLoading, setIsLoading] = useState(false);

    const handleSubmit = async (e) => {
        e.preventDefault();
        setIsLoading(true);
        
        try {
            await api.updateTrainParameters(parameters);
            // Show success notification
        } catch (error) {
            // Show error notification
        } finally {
            setIsLoading(false);
        }
    };

    const handleInputChange = (field, value) => {
        setParameters(prev => ({
            ...prev,
            [field]: parseFloat(value) || 0
        }));
    };

    return (
        <Card className="w-full max-w-2xl">
            <CardHeader>
                <CardTitle>Train Parameters</CardTitle>
            </CardHeader>
            <CardContent>
                <form onSubmit={handleSubmit} className="space-y-4">
                    <div className="grid grid-cols-2 gap-4">
                        <div>
                            <Label htmlFor="tractionMotors">Number of Traction Motors</Label>
                            <Input
                                id="tractionMotors"
                                type="number"
                                value={parameters.tractionMotors}
                                onChange={(e) => handleInputChange('tractionMotors', e.target.value)}
                            />
                        </div>
                        <div>
                            <Label htmlFor="axles">Number of Axles</Label>
                            <Input
                                id="axles"
                                type="number"
                                value={parameters.axles}
                                onChange={(e) => handleInputChange('axles', e.target.value)}
                            />
                        </div>
                        {/* Add more parameter inputs */}
                    </div>
                    
                    <Button type="submit" disabled={isLoading} className="w-full">
                        {isLoading ? 'Updating...' : 'Update Parameters'}
                    </Button>
                </form>
            </CardContent>
        </Card>
    );
}
```

### Phase 3: Electron Configuration

#### Step 1: Create Electron Main Process
Create `frontend/electron/main.js`:

```javascript
const { app, BrowserWindow, ipcMain } = require('electron');
const { spawn } = require('child_process');
const path = require('path');
const isDev = require('electron-is-dev');

let mainWindow;
let qtBackendProcess;

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1200,
        height: 800,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            preload: path.join(__dirname, 'preload.js')
        }
    });

    const startUrl = isDev 
        ? 'http://localhost:3000' 
        : `file://${path.join(__dirname, '../out/index.html')}`;
    
    mainWindow.loadURL(startUrl);

    if (isDev) {
        mainWindow.webContents.openDevTools();
    }
}

function startQtBackend() {
    const isWindows = process.platform === 'win32';
    const executableName = isWindows ? 'TrainSimulationApp.exe' : 'TrainSimulationApp';
    
    const backendPath = isDev 
        ? path.join(__dirname, '../../backend/build', executableName)
        : path.join(process.resourcesPath, 'backend', executableName);
    
    // Make executable on Linux/Mac
    if (!isWindows && isDev) {
        require('fs').chmodSync(backendPath, '755');
    }
    
    qtBackendProcess = spawn(backendPath, ['--server'], {
        stdio: 'pipe'
    });

    qtBackendProcess.stdout.on('data', (data) => {
        console.log(`Qt Backend: ${data}`);
    });

    qtBackendProcess.stderr.on('data', (data) => {
        console.error(`Qt Backend Error: ${data}`);
    });
}

app.whenReady().then(() => {
    startQtBackend();
    
    // Wait for backend to start, then create window
    setTimeout(() => {
        createWindow();
    }, 2000);
});

app.on('window-all-closed', () => {
    if (qtBackendProcess) {
        qtBackendProcess.kill();
    }
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

app.on('before-quit', () => {
    if (qtBackendProcess) {
        qtBackendProcess.kill();
    }
});
```

#### Step 2: Create Preload Script
Create `frontend/electron/preload.js`:

```javascript
const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('electronAPI', {
    // Backend communication helpers
    checkBackendHealth: () => ipcRenderer.invoke('check-backend-health'),
    restartBackend: () => ipcRenderer.invoke('restart-backend'),
    
    // File system operations
    selectFile: () => ipcRenderer.invoke('select-file'),
    saveFile: (data) => ipcRenderer.invoke('save-file', data),
    
    // App controls
    minimizeWindow: () => ipcRenderer.invoke('minimize-window'),
    closeWindow: () => ipcRenderer.invoke('close-window'),
});
```

#### Step 3: Update Package.json
Update `frontend/package.json`:

```json
{
  "name": "train-simulation-frontend",
  "version": "1.0.0",
  "main": "electron/main.js",
  "homepage": "./",
  "scripts": {
    "dev": "next dev",
    "build": "next build",
    "start": "next start",
    "electron": "electron .",
    "electron-dev": "concurrently \"npm run dev\" \"wait-on http://localhost:3000 && electron .\"",
    "build-electron": "npm run build && electron-builder",
    "dist": "npm run build && electron-builder --publish=never"
  },
  "build": {
    "appId": "com.trainSimulation.app",
    "productName": "Train Simulation App",
    "directories": {
      "output": "dist"
    },
    "files": [
      "out/**/*",
      "electron/**/*",
      "node_modules/**/*"
    ],
    "extraResources": [
      {
        "from": "../backend/build/",
        "to": "backend/",
        "filter": ["**/*"]
      }
    ],
    "linux": {
      "target": [
        {
          "target": "AppImage",
          "arch": ["x64"]
        },
        {
          "target": "rpm",
          "arch": ["x64"]
        },
        {
          "target": "deb",
          "arch": ["x64"]
        }
      ],
      "category": "Engineering"
    },
    "win": {
      "target": [
        {
          "target": "nsis",
          "arch": ["x64"]
        },
        {
          "target": "portable",
          "arch": ["x64"]
        }
      ]
    }
  }
}
```

### Phase 4: Build Scripts

#### Create Cross-Platform Build Scripts

**Linux Build Script** (`scripts/build-all.sh`):
```bash
#!/bin/bash
set -e

echo "Building Train Simulation Desktop App (Linux)..."

echo
echo "[1/3] Building Qt Backend..."
cd backend
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cd ../..

echo
echo "[2/3] Building Next.js Frontend..."
cd frontend
npm install
npm run build
cd ..

echo
echo "[3/3] Packaging Electron App..."
cd frontend
npm run dist
cd ..

echo
echo "Build complete! Check frontend/dist/ for the packages."
```

**Windows Build Script** (`scripts/build-all.bat`):
```batch
@echo off
echo Building Train Simulation Desktop App (Windows)...

echo.
echo [1/3] Building Qt Backend...
cd backend
if not exist build mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
mingw32-make -j%NUMBER_OF_PROCESSORS%
cd ..\..

echo.
echo [2/3] Building Next.js Frontend...
cd frontend
npm install
npm run build
cd ..

echo.
echo [3/3] Packaging Electron App...
cd frontend
npm run dist
cd ..

echo.
echo Build complete! Check frontend/dist/ for the executable.
pause
```

**Unified Node.js Build Script** (`scripts/cross-platform-build.js`):
```javascript
const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');
const os = require('os');

const isWindows = process.platform === 'win32';
const isLinux = process.platform === 'linux';

function runCommand(command, options = {}) {
    console.log(`Running: ${command}`);
    try {
        return execSync(command, { 
            stdio: 'inherit', 
            cwd: options.cwd || process.cwd(),
            ...options 
        });
    } catch (error) {
        console.error(`Command failed: ${command}`);
        process.exit(1);
    }
}

function buildQtBackend() {
    console.log('[1/3] Building Qt Backend...');
    
    const backendDir = path.join(__dirname, '..', 'backend');
    const buildDir = path.join(backendDir, 'build');
    
    // Create build directory
    if (!fs.existsSync(buildDir)) {
        fs.mkdirSync(buildDir, { recursive: true });
    }
    
    // Configure with CMake
    let cmakeGenerator = '';
    if (isWindows) {
        cmakeGenerator = '-G "MinGW Makefiles"';
    }
    
    runCommand(`cmake .. ${cmakeGenerator} -DCMAKE_BUILD_TYPE=Release`, { 
        cwd: buildDir 
    });
    
    // Build
    const makeCommand = isWindows 
        ? `mingw32-make -j${os.cpus().length}`
        : `make -j${os.cpus().length}`;
    
    runCommand(makeCommand, { cwd: buildDir });
    
    // Make executable on Linux
    if (isLinux) {
        const execPath = path.join(buildDir, 'TrainSimulationApp');
        if (fs.existsSync(execPath)) {
            fs.chmodSync(execPath, '755');
        }
    }
}

function buildFrontend() {
    console.log('[2/3] Building Next.js Frontend...');
    
    const frontendDir = path.join(__dirname, '..', 'frontend');
    
    runCommand('npm install', { cwd: frontendDir });
    runCommand('npm run build', { cwd: frontendDir });
}

function packageApp() {
    console.log('[3/3] Packaging Electron App...');
    
    const frontendDir = path.join(__dirname, '..', 'frontend');
    
    // Platform-specific build
    let buildCommand = 'npm run dist';
    if (process.argv.includes('--target')) {
        const targetIndex = process.argv.indexOf('--target');
        const target = process.argv[targetIndex + 1];
        buildCommand = `npm run dist -- --${target}`;
    }
    
    runCommand(buildCommand, { cwd: frontendDir });
}

function main() {
    console.log(`Building Train Simulation Desktop App (${process.platform})...`);
    console.log(`CPU cores: ${os.cpus().length}`);
    
    try {
        buildQtBackend();
        buildFrontend();
        packageApp();
        
        console.log('\nBuild complete! Check frontend/dist/ for the packages.');
        
        // List created packages
        const distDir = path.join(__dirname, '..', 'frontend', 'dist');
        if (fs.existsSync(distDir)) {
            console.log('\nCreated packages:');
            const files = fs.readdirSync(distDir);
            files.forEach(file => {
                const stat = fs.statSync(path.join(distDir, file));
                const sizeMB = (stat.size / (1024 * 1024)).toFixed(2);
                console.log(`  - ${file} (${sizeMB} MB)`);
            });
        }
    } catch (error) {
        console.error('Build failed:', error.message);
        process.exit(1);
    }
}

if (require.main === module) {
    main();
}

module.exports = { buildQtBackend, buildFrontend, packageApp };
```

**Usage:**
```bash
# Linux
chmod +x scripts/build-all.sh
./scripts/build-all.sh

# Windows
scripts\build-all.bat

# Cross-platform (Node.js)
node scripts/cross-platform-build.js

# Build for specific target
node scripts/cross-platform-build.js --target linux
node scripts/cross-platform-build.js --target win
```

---

## � Cross-Platform Build & Distribution

### GitHub Actions CI/CD Pipeline
Create `.github/workflows/build.yml` for automated cross-platform builds:

```yaml
name: Cross-Platform Build

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  build-linux:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    
    - name: Install Qt
      uses: jurplel/install-qt-action@v3
      with:
        version: '6.5.0'
        modules: 'qtcharts qtnetworkauth'
    
    - name: Install Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Build Qt Backend
      run: |
        cd backend
        mkdir build && cd build
        cmake .. -DCMAKE_BUILD_TYPE=Release
        make -j$(nproc)
    
    - name: Build Frontend
      run: |
        cd frontend
        npm install
        npm run build
        npm run dist
    
    - name: Upload Linux Artifacts
      uses: actions/upload-artifact@v3
      with:
        name: linux-build
        path: frontend/dist/*.AppImage

  build-windows:
    runs-on: windows-latest
    steps:
    - uses: actions/checkout@v3
    
    - name: Install Qt
      uses: jurplel/install-qt-action@v3
      with:
        version: '6.5.0'
        modules: 'qtcharts qtnetworkauth'
        arch: 'win64_mingw'
    
    - name: Install Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Build Qt Backend
      run: |
        cd backend
        mkdir build
        cd build
        cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
        mingw32-make -j%NUMBER_OF_PROCESSORS%
    
    - name: Build Frontend
      run: |
        cd frontend
        npm install
        npm run build
        npm run dist
    
    - name: Upload Windows Artifacts
      uses: actions/upload-artifact@v3
      with:
        name: windows-build
        path: frontend/dist/*.exe
```

### Local Cross-Platform Development

#### Option 1: Native Development (Recommended for you)
Since you're on Nobara Linux:

1. **Primary Development**: Continue on Linux
2. **Windows Testing**: Use VirtualBox/VMware with Windows 11
3. **Cross-compilation**: Use MinGW for Windows builds on Linux

```bash
# Install MinGW cross-compiler on Nobara/Fedora
sudo dnf install mingw64-gcc-c++ mingw64-qt6-qtbase-devel

# Cross-compile for Windows
mkdir backend/build-windows
cd backend/build-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-mingw64.cmake
make -j$(nproc)
```

#### Option 2: Docker Development Environment
Create `docker/Dockerfile.dev`:

```dockerfile
FROM ubuntu:22.04

# Install Qt and development tools
RUN apt-get update && apt-get install -y \
    qt6-base-dev qt6-charts-dev \
    cmake build-essential \
    nodejs npm \
    git curl

# Install MinGW for Windows cross-compilation
RUN apt-get install -y mingw-w64 \
    gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64

WORKDIR /app
COPY . .

# Development script
COPY docker/dev-setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/dev-setup.sh

CMD ["/bin/bash"]
```

#### Option 3: VM Setup for Windows Testing
1. **Download Windows 11 Dev VM** from Microsoft
2. **Install in VirtualBox**:
   ```bash
   sudo dnf install VirtualBox VirtualBox-guest-additions
   ```
3. **Setup development environment** in Windows VM
4. **Share project folder** between host and VM

### Platform-Specific Packaging

#### Linux Distribution Packages

**AppImage** (Universal Linux):
```json
// In frontend/package.json build section
"linux": {
  "target": [
    {
      "target": "AppImage",
      "arch": ["x64"]
    }
  ],
  "category": "Engineering",
  "description": "Train Simulation and Analysis Tool"
}
```

**RPM Package** (Fedora/RHEL/CentOS):
```json
{
  "target": "rpm",
  "arch": ["x64"]
}
```

**DEB Package** (Ubuntu/Debian):
```json
{
  "target": "deb",
  "arch": ["x64"]
}
```

#### Windows Installer Options

**NSIS Installer**:
```json
"win": {
  "target": [
    {
      "target": "nsis",
      "arch": ["x64"]
    }
  ],
  "publisherName": "Your Company Name"
}
```

**Portable Executable**:
```json
{
  "target": "portable",
  "arch": ["x64"]
}
```

---

## �🔌 Communication Layer

### API Endpoints Mapping

| Frontend Action          | HTTP Endpoint                     | Qt Backend Handler                                                                                            |
| ------------------------ | --------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| Update Train Parameters  | `POST /api/parameters/train`      | [`TrainDataHandler::storeFormInputs`](controllers/data/train_data_handler.cpp)                                |
| Update Electrical Params | `POST /api/parameters/electrical` | [`ElectricalDataHandler::storeFormInputs`](controllers/data/electrical_data_handler.cpp)                      |
| Start Simulation         | `POST /api/simulation/start`      | [`TrainSimulationHandler::simulateDynamicTrainMovement`](controllers/simulation/train_simulation_handler.cpp) |
| Get Results              | `GET /api/simulation/results`     | Access [`SimulationData`](models/simulation_data.h)                                                           |

### Data Flow Example
```
1. User inputs parameters in React form
2. Frontend sends POST request to Qt backend
3. Qt backend updates internal data structures
4. User clicks "Run Simulation"
5. Frontend sends simulation request
6. Qt backend executes simulation logic
7. Frontend polls for results
8. Qt backend returns simulation data
9. Frontend displays charts and tables
```

---

## 📦 Build & Distribution

### Development Mode

#### Linux (Your Current Setup)
```bash
# Terminal 1: Start Qt backend
cd backend/build
./TrainSimulationApp --server

# Terminal 2: Start Next.js dev server
cd frontend
npm run dev

# Terminal 3: Start Electron
cd frontend
npm run electron
```

#### Windows
```cmd
# Terminal 1: Start Qt backend
cd backend\build
TrainSimulationApp.exe --server

# Terminal 2: Start Next.js dev server
cd frontend
npm run dev

# Terminal 3: Start Electron
cd frontend
npm run electron
```

### Production Build

#### Cross-Platform (Recommended)
```bash
# Using Node.js unified script
node scripts/cross-platform-build.js

# Or platform-specific
chmod +x scripts/build-all.sh && ./scripts/build-all.sh  # Linux
scripts\build-all.bat  # Windows
```

#### Manual Build Steps
```bash
# Linux
cd backend && mkdir -p build && cd build && cmake .. && make -j$(nproc)
cd ../../frontend && npm install && npm run build && npm run dist

# Windows
cd backend && mkdir build && cd build && cmake .. -G "MinGW Makefiles" && mingw32-make
cd ../../frontend && npm install && npm run build && npm run dist
```

---

## 🐛 Troubleshooting

### Common Issues

#### Qt Backend Not Starting
- Check if port 8080 is available
- Verify Qt Network module is properly linked
- Check console output for error messages

#### Frontend Can't Connect to Backend
- Ensure CORS is properly configured in Qt server
- Check if backend is running before frontend starts
- Verify API endpoint URLs match

#### Electron Build Fails
- Check if backend executables are in correct path
- Verify all dependencies are installed
- Check electron-builder configuration

### Debug Commands

#### Linux
```bash
# Check if backend is responding
curl http://localhost:8080/api/health

# Check backend logs
./TrainSimulationApp --server --verbose

# Debug Electron
cd frontend && npm run electron-dev

# Check Qt dependencies
ldd ./TrainSimulationApp

# Monitor process
htop | grep TrainSimulation
```

#### Windows
```cmd
# Check if backend is responding (PowerShell)
Invoke-WebRequest -Uri http://localhost:8080/api/health

# Check backend logs
TrainSimulationApp.exe --server --verbose

# Debug Electron
cd frontend && npm run electron-dev

# Check dependencies (PowerShell)
Get-Process | Where-Object {$_.ProcessName -like "*TrainSimulation*"}
```

#### Cross-Platform Debug Script
Create `scripts/debug.js`:
```javascript
const { spawn } = require('child_process');
const axios = require('axios');

async function checkBackend() {
    try {
        const response = await axios.get('http://localhost:8080/api/health');
        console.log('✅ Backend is running:', response.data);
    } catch (error) {
        console.log('❌ Backend not responding:', error.message);
    }
}

// Run: node scripts/debug.js
checkBackend();
```

---

## 🚀 Next Steps & Cross-Platform Strategy

### Recommended Development Approach

#### Phase 1: Linux Development (Your Current Setup)
1. **Start with Qt HTTP server**: Modify your existing Qt app on Linux
2. **Test API endpoints**: Use curl to verify backend responses
3. **Build basic frontend**: Create simple Next.js components
4. **Local integration**: Get everything working on Linux first

#### Phase 2: Cross-Platform Preparation
1. **Setup CI/CD**: Implement GitHub Actions for automated builds
2. **Create build scripts**: Use the provided Node.js unified build script
3. **Test Windows VM**: Setup Windows development environment
4. **Package testing**: Verify packages work on both platforms

#### Phase 3: Production Deployment
1. **Cross-compile testing**: Use MinGW for Windows builds from Linux
2. **Distribution strategy**: AppImage for Linux, NSIS installer for Windows
3. **Auto-updater**: Implement electron-updater for seamless updates
4. **Error handling**: Add comprehensive error boundaries and fallbacks

### Cross-Platform Development Tips

#### For Your Current Linux Setup:
```bash
# Install Windows cross-compilation tools
sudo dnf install mingw64-gcc-c++ mingw64-qt6-qtbase-devel

# Create Windows build without VM
mkdir backend/build-windows
cd backend/build-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-mingw64.cmake
make -j$(nproc)
```

#### Electron Builder Platform Targets:
```bash
# Build for current platform
npm run dist

# Build for all platforms (if you have the tools)
npm run dist -- --linux --win

# Build specific packages
npm run dist -- --linux AppImage
npm run dist -- --win nsis
```

#### Testing Strategy:
1. **Primary development**: Linux (your current setup)
2. **Cross-platform testing**: 
   - Windows VM for testing Windows builds
   - GitHub Actions for automated cross-platform verification
3. **Distribution testing**: Test packages on clean VMs

### Recommended Workflow:
1. Develop and test everything on your Linux machine first
2. Use the unified Node.js build script for consistency
3. Setup GitHub Actions for automated Windows builds
4. Test final packages on Windows VM before release
5. Use AppImage for Linux distribution (works everywhere)
6. Use NSIS installer for Windows (professional experience)

This approach lets you stay productive on your preferred Linux environment while ensuring Windows compatibility! -->