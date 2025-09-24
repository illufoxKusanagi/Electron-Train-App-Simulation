const { app, BrowserWindow, ipcMain } = require("electron");
const { spawn } = require("child_process");
const path = require("path");

let mainWindow;
let backendProc;

function startBackend() {
    console.log("Starting Qt backend...");

    // Path to the backend run script
    const scriptPath = path.join(__dirname, "..", "backend", "scripts", "dev-run.sh");

    backendProc = spawn("bash", [scriptPath], {
        cwd: path.join(__dirname, "..", "backend"),
    });

    backendProc.stdout.on("data", (data) => {
        console.log(`[Qt Backend] ${data}`);
    });

    backendProc.stderr.on("data", (data) => {
        console.error(`[Qt Backend ERROR] ${data}`);
    });

    backendProc.on("close", (code) => {
        console.log(`Qt Backend exited with code ${code}`);
    });
}

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1200,
        height: 800,
        webPreferences: {
            preload: path.join(__dirname, "preload.js"),
            contextIsolation: true,
            nodeIntegration: false,
        },
    });

    // In development: Next.js runs at localhost:3000
    mainWindow.loadURL("http://localhost:3000");

    // Open DevTools in development
    if (process.env.NODE_ENV === "development") {
        mainWindow.webContents.openDevTools();
    }
}

app.whenReady().then(() => {
    createWindow();
    startBackend();
});

app.on("window-all-closed", () => {
    if (process.platform !== "darwin") {
        if (backendProc) {
            backendProc.kill();
        }
        app.quit();
    }
});

app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});

// IPC bridge for backend communication
ipcMain.handle("backend-request", async (_event, endpoint, data) => {
    try {
        // This is a placeholder - implement actual backend communication
        console.log(`Backend request to: ${endpoint}`, data);
        return { success: true, endpoint, data };
    } catch (error) {
        console.error("Backend request failed:", error);
        return { success: false, error: error.message };
    }
});

// const { app, BrowserWindow } = require('electron');
// const { spawn } = require('child_process');
// const path = require('path');
// const net = require('net');

// let mainWindow;
// let qtBackendProcess;

// function createWindow() {
//     mainWindow = new BrowserWindow({
//         width: 1200,
//         height: 800,
//         webPreferences: {
//             nodeIntegration: false,
//             contextIsolation: true,
//             preload: path.join(__dirname, 'preload.js')
//         }
//     });

//     mainWindow.loadURL('http://localhost:3000');
//     mainWindow.webContents.openDevTools();

//     mainWindow.on('closed', () => {
//         mainWindow = null;
//     });
// }

// function waitForPort(port, retries = 10, delay = 500) {
//     return new Promise((resolve, reject) => {
//         let attempts = 0;

//         const check = () => {
//             const socket = net.createConnection(port, '127.0.0.1');
//             socket.once('connect', () => {
//                 socket.end();
//                 resolve();
//             });
//             socket.once('error', () => {
//                 attempts++;
//                 if (attempts < retries) {
//                     setTimeout(check, delay);
//                 } else {
//                     reject(new Error(`Backend not responding on port ${port}`));
//                 }
//             });
//         };

//         check();
//     });
// }

// function startQtBackend() {
//     const execName = process.platform === 'win32'
//         ? 'TrainSimulationApp.exe'
//         : 'TrainSimulationApp';

//     const backendPath = path.join(__dirname, '../../backend/bin', execName);

//     console.log('🔧 Starting Qt backend from:', backendPath);

//     qtBackendProcess = spawn(backendPath, ['--headless', '--port=8080'], {
//         stdio: 'inherit'
//     });

//     qtBackendProcess.on('error', (error) => {
//         console.error('❌ Failed to start Qt backend:', error);
//     });

//     return waitForPort(8080);
// }

// app.whenReady().then(async () => {
//     console.log('🚀 Starting Electron app...');

//     try {
//         await startQtBackend();
//         console.log('✅ Backend is ready on port 8080');
//         createWindow();
//     } catch (err) {
//         console.error(err.message);
//         app.quit();
//     }
// });

// app.on('window-all-closed', () => {
//     if (qtBackendProcess) qtBackendProcess.kill();
//     if (process.platform !== 'darwin') app.quit();
// });

// app.on('before-quit', () => {
//     if (qtBackendProcess) qtBackendProcess.kill();
// });
