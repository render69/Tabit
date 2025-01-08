#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QToolBar>
#include <QAction>
#include <QTabWidget>

class BrowserWindow : public QMainWindow {
    Q_OBJECT

public:
    BrowserWindow();

private slots:
    void navigateToUrl();
    void updateUrlBar(const QUrl &url);
    void goBack();
    void goForward();
    void refreshPage();
    void stopLoading();
    void newTab();
    void closeTab(int index);
    void updateTabTitle(const QString &title);

private:
    QLineEdit *urlBar;
    QTabWidget *tabWidget;
    QToolBar *toolbar;
    QWebEngineView *createWebView();
};

#endif // BROWSERWINDOW_H