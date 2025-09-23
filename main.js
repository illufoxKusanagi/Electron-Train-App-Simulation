const { app, BrowserWindow } = require('electron');
const { spawn } = require('child_process');
const path = require('path');

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

    // Load the Next.js dev server
    mainWindow.loadURL('http://localhost:3000');

    mainWindow.webContents.openDevTools();

    mainWindow.on('closed', () => {
        mainWindow = null;
    });
}

function startQtBackend() {
    const backendPath = path.join(__dirname, '../../backend/build/Desktop_Qt_6_9_2-Debug/TrainSimulationApp');

    console.log('🔧 Starting Qt backend from:', backendPath);

    qtBackendProcess = spawn(backendPath, ['--headless', '--port=8080'], {
        stdio: 'inherit'
    });

    qtBackendProcess.on('error', (error) => {
        console.error('❌ Failed to start Qt backend:', error);
    });
}

app.whenReady().then(() => {
    console.log('🚀 Starting Electron app...');

    // Start Qt backend first
    startQtBackend();

    // Wait a bit for backend to start, then create window
    setTimeout(() => {
        createWindow();
        console.log('✅ Electron window created');
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