#ifndef CUSTOMWEBPAGE_H
#define CUSTOMWEBPAGE_H

#include <QWebEnginePage>

class CustomWebPage : public QWebEnginePage {
    Q_OBJECT

public:
    explicit CustomWebPage(QObject *parent = nullptr);

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame) override;
};

#endif // CUSTOMWEBPAGE_H
