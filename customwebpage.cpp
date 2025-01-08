#include "customwebpage.h"

#include <QDesktopServices>
#include <QDebug>

CustomWebPage::CustomWebPage(QObject *parent) : QWebEnginePage(parent) {}

bool CustomWebPage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame) {
    if (type == QWebEnginePage::NavigationTypeLinkClicked) {
        if (isMainFrame) {
            setUrl(url);
            return false;
        } else {
            return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
        }
    }
    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}
