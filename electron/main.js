const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("path");

let mainWindow;

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1200,
        height: 800,
        webPreferences: {
            preload: path.join(__dirname, "preload.js"),
            contextIsolation: true,
            nodeIntegration: false,
        },
        show: false // Don't show until ready
    });

    // Load the frontend
    mainWindow.loadURL("http://localhost:3000");

    // Show when ready
    mainWindow.once('ready-to-show', () => {
        mainWindow.show();
        console.log('🎉 Electron app is ready!');
    });

    // Handle failed loading
    mainWindow.webContents.on('did-fail-load', () => {
        console.log('⏳ Frontend not ready, retrying in 2 seconds...');
        setTimeout(() => {
            mainWindow.reload();
        }, 2000);
    });

    if (process.env.NODE_ENV === "development") {
        mainWindow.webContents.openDevTools();
    }
}

app.whenReady().then(() => {
    console.log('🚀 Starting Electron app...');
    createWindow();
});

app.on("window-all-closed", () => {
    if (process.platform !== "darwin") {
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
        console.log(`Backend request to: ${endpoint}`, data);
        return { success: true, endpoint, data };
    } catch (error) {
        console.error("Backend request failed:", error);
        return { success: false, error: error.message };
    }
});