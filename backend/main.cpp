#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "core/appcontext.h"
#include "http_server/http_server.h"

int main(int argc, char *argv[])
{
    // Edited here: Use QCoreApplication for headless server (no GUI)
    QCoreApplication app(argc, argv);
    QCoreApplication::setOrganizationName("PT INKA Persero");
    QCoreApplication::setApplicationName("Train Simulation App");
    
    // Check if running in server mode
    bool headless = false;
    quint16 port = 8080; // Default port
    
    for (int i = 1; i < argc; i++) {
        if (QString(argv[i]) == "--headless") {
            headless = true;
        }
        if (QString(argv[i]).startsWith("--port=")) {
            port = QString(argv[i]).mid(7).toInt();
        }
    }
//ok, but why the issue is remain the same? i can't run electron-dev with desktop mode, but it will run on browser instead    
    if (headless) {
        AppContext context;
        HttpServer server(context);
        
        if (server.startServer(port)) {
            qDebug() << "✅ Train Simulation Backend Server started on port" << port;
            qInfo() << "Server started successfully on port:" << server.getPort();
            qInfo() << "Available endpoints:";
            qInfo() << "  GET  /status - Server status";
            qInfo() << "  GET  /api/health - Health check";
            qInfo() << "  GET  /api/parameters/train - Get train parameters";
            qInfo() << "  POST /api/parameters/train - Update train parameters";
            qInfo() << "  GET  /api/parameters/electrical - Get electrical parameters";
            qInfo() << "  POST /api/parameters/electrical - Update electrical parameters";
            qInfo() << "  GET  /api/parameters/running - Get running parameters";
            qInfo() << "  POST /api/parameters/running - Update running parameters";
            qInfo() << "  GET  /api/parameters/track - Get track parameters";
            qInfo() << "  POST /api/parameters/track - Update track parameters";
            qInfo() << "  POST /api/simulation/start - Start simulation";
            qInfo() << "  GET  /api/simulation/status - Get simulation status";
            qInfo() << "  GET  /api/simulation/results - Get simulation results";
            qInfo() << "  POST /api/export/results - Export results to CSV";
            return app.exec();
        } else {
            qDebug() << "❌ Failed to start server on port" << port;
            return 1;
        }
        // qInfo() << "Starting Train Simulation Backend Server...";
        
        // // Initialize application context with all data structures
        // AppContext context;
        
        // // Create and start HTTP server
        // HttpServer server(context);
        // if (!server.startServer(port)) {
        //     qCritical() << "Failed to start HTTP server";
        //     return 1;
        // }
        
        
        return app.exec();
    } else {
        // Run with GUI (your existing code)
        qInfo() << "Starting with GUI mode...";
        // Add your existing GUI initialization code here
        return app.exec();
    }
}

// #include <QCoreApplication>  // Changed from QApplication
// #include <QDebug>
// #include <QTimer>
// #include "core/appcontext.h"
// #include "http_server/http_server.h"

// int main(int argc, char *argv[]) {
//     QCoreApplication app(argc, argv);  // No GUI needed
    
//     // Parse command line arguments
//     bool headless = false;
//     int port = 8080;
    
//     for (int i = 1; i < argc; i++) {
//         if (QString(argv[i]) == "--server") {
//             headless = true;
//         } else if (QString(argv[i]) == "--port" && i + 1 < argc) {
//             port = QString(argv[i + 1]).toInt();
//             i++; // Skip next argument
//         }
//     }
    
//     if (!headless) {
//         qDebug() << "Usage: TrainSimulationApp --server [--port 8080]";
//         return 1;
//     }
    
//     // Initialize application context
//     AppContext context;
    
//     // Start HTTP server
//     HttpServer server(context);
//     if (!server.startServer(port)) {
//         qDebug() << "Failed to start server. Exiting.";
//         return 1;
//     }
    
//     qDebug() << "Train Simulation Backend is running...";
//     qDebug() << "Press Ctrl+C to stop";
    
//     return app.exec();
// }

// // #include "core/appcontext.h"
// // #include "mainwindow/mainwindow.h"
// // #include "widgets/login_dialog_widget.h"
// // #include "widgets/message_box_widget.h"
// // #include <QApplication>
// // #include <QDebug>
// // #include <QIcon>
// // #include <QInputDialog>
// // #include <QSize>

// // int main(int argc, char *argv[]) {
// //   QApplication app(argc, argv);
// //   QCoreApplication::setOrganizationName("PT INKA Persero");
// //   QCoreApplication::setApplicationName("Train Simulation App");
// //   QIcon appIcon;
// //   appIcon.addFile(":/icons/icons/trainSimulationAppLogo.png", QSize(64, 64));
// //   app.setWindowIcon(appIcon);
// //   app.setStyleSheet("QWidget { background-color: white; color: black; }");
// //   AppContext context;
// //   bool loggedIn = false;
// //   LoginDialogWidget loginDialog;
// //   QObject::connect(
// //       &loginDialog, &LoginDialogWidget::loginAttempt,
// //       [&context, &loggedIn, &loginDialog](const QString &username,
// //                                           const QString &password) {
// //         if (context.authManager->login(username, password)) {
// //           loggedIn = true;
// //           MessageBoxWidget messageBox("Login Successful",
// //                                       "Welcome to the Train Simulation App!",
// //                                       MessageBoxWidget::Information);
// //           loginDialog.accept();
// //         } else {
// //           MessageBoxWidget messageBox(
// //               "Login Failed", "Invalid username or password. Please try again.",
// //               MessageBoxWidget::Critical);
// //         }
// //       });
// //   int result = loginDialog.exec();
// //   if (result == QDialog::Accepted && loggedIn) {
// //     MainWindow mainWindow(context);
// //     mainWindow.show();
// //     return app.exec();
// //   } else {
// //     return 0;
// //   }
// // }
