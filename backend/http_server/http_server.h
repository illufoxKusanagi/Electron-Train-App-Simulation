#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <QObject>
#include <QHttpServer>
#include <QTcpServer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <memory>
#include "core/appcontext.h"
#include "api_handler.h"

class HttpServer : public QObject {
    Q_OBJECT

public:
    explicit HttpServer(AppContext &context, QObject *parent = nullptr);
    bool startServer(quint16 port = 0); // Edited here: Use 0 to let OS pick available port
    void stopServer();
    quint16 getPort() const;

private:
    void setupRoutes();
    QJsonObject parseRequestBody(const QHttpServerRequest &request);
    
    QHttpServer *m_httpServer;
    std::unique_ptr<QTcpServer> m_tcpServer;
    ApiHandler *m_apiHandler;
    AppContext &m_context;
    quint16 m_port;
};

#endif // HTTP_SERVER_H