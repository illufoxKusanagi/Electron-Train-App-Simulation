#!/bin/bash
set -e

echo "🔍 Smart Qt Backend Runner..."

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BACKEND_DIR="$(dirname "$SCRIPT_DIR")"

echo "Backend directory: $BACKEND_DIR"
cd "$BACKEND_DIR"

# Qt Configuration
QT_VERSION="6.9.2"
QT_DIR="/opt/Qt/${QT_VERSION}/gcc_64"
BUILD_TYPE="Debug"
BUILD_DIR="build-TrainSimulationApp-Desktop_Qt_${QT_VERSION//\./_}_gcc_64-${BUILD_TYPE}"

# Function to check if executable exists and is recent
check_existing_build() {
    local build_patterns=(
        "${BACKEND_DIR}/${BUILD_DIR}"
        "${BACKEND_DIR}/../${BUILD_DIR}"
        "${BACKEND_DIR}/build-TrainSimulationApp-Desktop_Qt_*"
        "${BACKEND_DIR}/../build-TrainSimulationApp-Desktop_Qt_*"
    )
    
    for pattern in "${build_patterns[@]}"; do
        for dir in $pattern; do
            if [ -d "$dir" ]; then
                echo "📁 Found build directory: $dir"
                
                # Check for executable
                local possible_exes=(
                    "$dir/TrainSimulationApp"
                    "$dir/bin/TrainSimulationApp"
                    "$dir/Debug/TrainSimulationApp"
                    "$dir/Release/TrainSimulationApp"
                )
                
                for exe in "${possible_exes[@]}"; do
                    if [ -f "$exe" ] && [ -x "$exe" ]; then
                        # Check if executable is newer than source files
                        local newest_source=$(find . -name "*.cpp" -o -name "*.h" -o -name "CMakeLists.txt" 2>/dev/null | xargs ls -t 2>/dev/null | head -n1)
                        if [ -n "$newest_source" ] && [ "$exe" -nt "$newest_source" ]; then
                            echo "✅ Found recent executable: $exe"
                            EXECUTABLE="$exe"
                            EXISTING_BUILD_DIR="$dir"
                            return 0
                        else
                            echo "⚠️  Executable exists but is older than source files"
                        fi
                    fi
                done
            fi
        done
    done
    return 1
}

# Function to build from scratch
build_from_scratch() {
    echo "🔨 Building from scratch..."
    
    # Set up Qt environment
    export PATH="${QT_DIR}/bin:$PATH"
    export LD_LIBRARY_PATH="${QT_DIR}/lib:$LD_LIBRARY_PATH"
    export QT_PLUGIN_PATH="${QT_DIR}/plugins"
    export QML_IMPORT_PATH="${QT_DIR}/qml"
    export QT_QPA_PLATFORM_PLUGIN_PATH="${QT_DIR}/plugins/platforms"
    export CMAKE_PREFIX_PATH="${QT_DIR}"
    export CMAKE_BUILD_TYPE="${BUILD_TYPE}"
    export Qt6_DIR="${QT_DIR}/lib/cmake/Qt6"
    export CC="/usr/bin/gcc"
    export CXX="/usr/bin/g++"
    export CMAKE_C_COMPILER="/usr/bin/gcc"
    export CMAKE_CXX_COMPILER="/usr/bin/g++"
    
    # Create and enter build directory
    mkdir -p "${BUILD_DIR}"
    cd "${BUILD_DIR}"
    
    # Configure with CMake
    echo "🔧 Configuring with CMake..."
    cmake \
        -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} \
        -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH="${QT_DIR}/lib/cmake/Qt6/qt.toolchain.cmake" \
        -DQT_QMAKE_EXECUTABLE:FILEPATH="${QT_DIR}/bin/qmake" \
        -DCMAKE_PREFIX_PATH:PATH="${QT_DIR}" \
        -DCMAKE_C_COMPILER:FILEPATH="${CMAKE_C_COMPILER}" \
        -DCMAKE_CXX_COMPILER:FILEPATH="${CMAKE_CXX_COMPILER}" \
        -DCMAKE_INSTALL_PREFIX:PATH="${BUILD_DIR}/install" \
        ..
    
    if [ $? -ne 0 ]; then
        echo "❌ CMake configuration failed"
        exit 1
    fi
    
    # Build
    echo "🔨 Building project..."
    cmake --build . --config ${BUILD_TYPE} -- -j$(nproc)
    
    if [ $? -ne 0 ]; then
        echo "❌ Build failed"
        exit 1
    fi
    
    # Find executable
    local possible_exes=(
        "./TrainSimulationApp"
        "./bin/TrainSimulationApp"
        "./${BUILD_TYPE}/TrainSimulationApp"
        "./Debug/TrainSimulationApp"
        "./Release/TrainSimulationApp"
    )
    
    for exe in "${possible_exes[@]}"; do
        if [ -f "$exe" ] && [ -x "$exe" ]; then
            EXECUTABLE="$exe"
            break
        fi
    done
    
    cd "$BACKEND_DIR"
}

# Function to run the executable
run_executable() {
    if [ -n "$EXECUTABLE" ]; then
        echo "🚀 Starting backend server: $EXECUTABLE"
        
        # Set up Qt runtime environment
        export LD_LIBRARY_PATH="${QT_DIR}/lib:$LD_LIBRARY_PATH"
        export QT_PLUGIN_PATH="${QT_DIR}/plugins"
        
        # Create a PID file to signal that backend is starting
        echo $$ > /tmp/qt-backend.pid
        
        # Run the executable
        if [[ "$EXECUTABLE" == ./* ]]; then
            # Relative path, need to be in build directory
            if [ -n "$EXISTING_BUILD_DIR" ]; then
                cd "$EXISTING_BUILD_DIR"
            else
                cd "$BUILD_DIR"
            fi
        fi
        
        $EXECUTABLE --headless --port=8080
    else
        echo "❌ No executable found!"
        exit 1
    fi
}

# Main execution
EXECUTABLE=""
EXISTING_BUILD_DIR=""

echo "🔍 Checking for existing builds..."
if check_existing_build; then
    echo "✅ Using existing build"
    run_executable
else
    echo "🏗️  No recent build found, building from scratch..."
    build_from_scratch
    run_executable
fi