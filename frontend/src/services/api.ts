import axios, { AxiosInstance } from "axios";

const API_BASE_URL = "http://localhost:8080";

class TrainSimulationAPI {
  private client: AxiosInstance;

  constructor() {
    this.client = axios.create({
      baseURL: API_BASE_URL,
      timeout: 5000,
      headers: {
        "Content-Type": "application/json",
      },
    });
  }

  // Health check
  async checkHealth(): Promise<{ status: string; dataStatus: string }> {
    const response = await this.client.get("/api/health");
    return response.data;
  }

  // Test parameter update
  async testParameterUpdate(): Promise<any> {
    const testParams = {
      tractionMotors: 4,
      axles: 8,
      wheelDiameter: 860,
    };
    const response = await this.client.post(
      "/api/parameters/train",
      testParams
    );
    return response.data;
  }
}

export const api = new TrainSimulationAPI();
