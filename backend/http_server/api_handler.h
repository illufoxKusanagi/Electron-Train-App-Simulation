#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QHttpServerResponse>
#include "core/appcontext.h"
#include "controllers/data/train_data_handler.h"
#include "controllers/data/electrical_data_handler.h"
#include "controllers/data/running_data_handler.h"
#include "controllers/data/track_data_handler.h"
#include "controllers/simulation/train_simulation_handler.h"
#include "controllers/output/csv_output_handler.h"

class ApiHandler : public QObject
{
    Q_OBJECT

public:
    explicit ApiHandler(AppContext &context, QObject *parent = nullptr);

    // Health check
    QHttpServerResponse handleHealthCheck();
    
    // Train parameters
    QHttpServerResponse handleGetTrainParameters();
    QHttpServerResponse handleUpdateTrainParameters(const QJsonObject &data);
    
    // Electrical parameters
    QHttpServerResponse handleGetElectricalParameters();
    QHttpServerResponse handleUpdateElectricalParameters(const QJsonObject &data);
    
    // Running parameters
    QHttpServerResponse handleGetRunningParameters();
    QHttpServerResponse handleUpdateRunningParameters(const QJsonObject &data);
    
    // Track parameters
    QHttpServerResponse handleGetTrackParameters();
    QHttpServerResponse handleUpdateTrackParameters(const QJsonObject &data);
    
    // Simulation control
    QHttpServerResponse handleStartSimulation(const QJsonObject &data);
    QHttpServerResponse handleGetSimulationStatus();
    QHttpServerResponse handleGetSimulationResults();
    
    // Export functionality
    QHttpServerResponse handleExportResults(const QJsonObject &data);

private:
    AppContext &m_context;
    
    // Edited here: Fixed handler member variable types to match actual classes
    TrainDataHandler *m_trainDataHandler;
    ElectricalDataHandler *m_electricalDataHandler;
    RunningDataHandler *m_runningDataHandler;
    TrackDataHandler *m_trackDataHandler;
    TrainSimulationHandler *m_simulationHandler;
    CsvOutputHandler *m_csvOutputHandler;
};

#endif // API_HANDLER_H

// #ifndef API_HANDLER_H
// #define API_HANDLER_H

// #include <QObject>
// #include <QJsonObject>
// #include <QHttpServerResponse>
// #include "core/appcontext.h"
// #include "controllers/data/train_data_handler.h"
// #include "controllers/data/electrical_data_handler.h"
// #include "controllers/data/running_data_handler.h"
// #include "controllers/data/track_data_handler.h"
// #include "controllers/simulation/train_simulation_handler.h"
// #include "controllers/output/csv_output_handler.h"

// class ApiHandler : public QObject
// {
//     Q_OBJECT

// public:
//     explicit ApiHandler(AppContext &context, QObject *parent = nullptr);

//     // Health check
//     QHttpServerResponse handleHealthCheck();
    
//     // Train parameters
//     QHttpServerResponse handleGetTrainParameters();
//     QHttpServerResponse handleUpdateTrainParameters(const QJsonObject &data);
    
//     // Electrical parameters
//     QHttpServerResponse handleGetElectricalParameters();
//     QHttpServerResponse handleUpdateElectricalParameters(const QJsonObject &data);
    
//     // Running parameters
//     QHttpServerResponse handleGetRunningParameters();
//     QHttpServerResponse handleUpdateRunningParameters(const QJsonObject &data);
    
//     // Track parameters - Edited here: Added missing track parameter methods
//     QHttpServerResponse handleGetTrackParameters();
//     QHttpServerResponse handleUpdateTrackParameters(const QJsonObject &data);
    
//     // Simulation control
//     QHttpServerResponse handleStartSimulation(const QJsonObject &data);
//     QHttpServerResponse handleGetSimulationStatus();
//     QHttpServerResponse handleGetSimulationResults();
    
//     // Export functionality
//     QHttpServerResponse handleExportResults(const QJsonObject &data);

// private:
//     AppContext &m_context;
    
//     // Edited here: Fixed handler member variable types to match actual classes
//     TrainDataHandler *m_trainDataHandler;
//     ElectricalDataHandler *m_electricalDataHandler;
//     RunningDataHandler *m_runningDataHandler;
//     TrackDataHandler *m_trackDataHandler;
//     TrainSimulationHandler *m_simulationHandler;
//     CsvOutputHandler *m_csvOutputHandler;
// };

// #endif // API_HANDLER_H