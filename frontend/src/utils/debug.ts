export const debugAPI = {
  async testEndpoints() {
    const endpoints = [
      "/api/health",
      "/api/parameters/train",
      "/api/simulation/start",
      "/api/simulation/results",
    ];

    const results = [];

    for (const endpoint of endpoints) {
      try {
        const response = await fetch(`http://localhost:8080${endpoint}`, {
          method:
            endpoint.includes("parameters") ||
            endpoint.includes("simulation/start")
              ? "POST"
              : "GET",
          headers: { "Content-Type": "application/json" },
          body: endpoint.includes("parameters")
            ? JSON.stringify({ test: true })
            : undefined,
        });

        results.push({
          endpoint,
          status: response.status,
          success: response.ok,
        });
      } catch (error) {
        results.push({
          endpoint,
          status: "ERROR",
          success: false,
          error: error,
        });
      }
    }

    return results;
  },
};
