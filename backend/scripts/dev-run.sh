#!/bin/bash
set -e

# Ensure build directory exists
mkdir -p build
cd build

# Configure & build
cmake ..
cmake --build . -- -j$(nproc)

# Go back to project root (so relative paths are consistent)
cd ..

# Run the backend binary from the fixed bin/ folder
./bin/TrainSimulationApp --headless --port=8080
