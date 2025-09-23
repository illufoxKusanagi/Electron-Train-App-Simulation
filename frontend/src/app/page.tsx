"use client";

import { useState, useEffect } from "react";
import { api } from "@/services/api";

export default function Home() {
  const [backendStatus, setBackendStatus] = useState<string>("Checking...");
  const [testResult, setTestResult] = useState<string>("");

  useEffect(() => {
    checkBackendConnection();
  }, []);

  const checkBackendConnection = async () => {
    try {
      const health = await api.checkHealth();
      setBackendStatus(`✅ Backend Connected: ${health.dataStatus}`);
    } catch (error) {
      setBackendStatus(`❌ Backend Error: ${error}`);
    }
  };

  const testParameterUpdate = async () => {
    try {
      const result = await api.testParameterUpdate();
      setTestResult(`✅ Parameter Update: ${result}`);
    } catch (error) {
      setTestResult(`❌ Parameter Error: ${error}`);
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
