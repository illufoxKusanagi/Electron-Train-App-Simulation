const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld("backend", {
    request: (endpoint, data) => ipcRenderer.invoke("backend-request", endpoint, data),
});

contextBridge.exposeInMainWorld("electron", {
    versions: process.versions,
});

contextBridge.exposeInIsolatedWorld("electronApi", {
    toggleDevTools: () => ipcRenderer.invoke('toggle-devtools'),
    platform: process.platform,
    version: process.versions.electron,
    isElectron: true,
})

// const { contextBridge } = require("electron");

// // contextBridge.exposeInMainWorld("electronAPI", {
// // });
// const { contextBridge, ipcRenderer } = require("electron");
// contextBridge.exposeInMainWorld("backend", {
//     request: (path, body) => ipcRenderer.invoke("backend-request", path, body),
// });
