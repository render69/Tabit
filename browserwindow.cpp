#include "browserwindow.h"
#include "customwebpage.h"

#include <QVBoxLayout>
#include <QAction>

BrowserWindow::BrowserWindow() {
    setWindowTitle("Tabit");
    setMinimumSize(1024, 768);
    toolbar = new QToolBar(this);
    addToolBar(toolbar);
    QAction *backAction = toolbar->addAction("Back");
    QAction *forwardAction = toolbar->addAction("Forward");
    QAction *refreshAction = toolbar->addAction("Refresh");
    QAction *stopAction = toolbar->addAction("Stop");
    QAction *newTabAction = toolbar->addAction("New Tab");
    urlBar = new QLineEdit(this);
    toolbar->addWidget(urlBar);
    QAction *goAction = toolbar->addAction("Go");
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    connect(goAction, &QAction::triggered, this, &BrowserWindow::navigateToUrl);
    connect(urlBar, &QLineEdit::returnPressed, this, &BrowserWindow::navigateToUrl);
    connect(backAction, &QAction::triggered, this, &BrowserWindow::goBack);
    connect(forwardAction, &QAction::triggered, this, &BrowserWindow::goForward);
    connect(refreshAction, &QAction::triggered, this, &BrowserWindow::refreshPage);
    connect(stopAction, &QAction::triggered, this, &BrowserWindow::stopLoading);
    connect(newTabAction, &QAction::triggered, this, &BrowserWindow::newTab);
    newTab();
}

void BrowserWindow::navigateToUrl() {
    QWebEngineView *currentWebView = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (currentWebView) {
        QString url = urlBar->text();
        if (!url.startsWith("http://") && !url.startsWith("https://")) {
            url.prepend("https://");
        }
        currentWebView->setUrl(QUrl(url));
    }
}

void BrowserWindow::updateUrlBar(const QUrl &url) {
    urlBar->setText(url.toString());
}

void BrowserWindow::goBack() {
    QWebEngineView *currentWebView = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (currentWebView) {
        currentWebView->back();
    }
}

void BrowserWindow::goForward() {
    QWebEngineView *currentWebView = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (currentWebView) {
        currentWebView->forward();
    }
}

void BrowserWindow::refreshPage() {
    QWebEngineView *currentWebView = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (currentWebView) {
        currentWebView->reload();
    }
}

void BrowserWindow::stopLoading() {
    QWebEngineView *currentWebView = qobject_cast<QWebEngineView*>(tabWidget->currentWidget());
    if (currentWebView) {
        currentWebView->stop();
    }
}

void BrowserWindow::newTab() {
    QWebEngineView *newWebView = createWebView();
    tabWidget->addTab(newWebView, "New Tab");
    tabWidget->setCurrentWidget(newWebView);
}

void BrowserWindow::closeTab(int index) {
    QWidget *widget = tabWidget->widget(index);
    tabWidget->removeTab(index);
    delete widget;
}

QWebEngineView* BrowserWindow::createWebView() {
    QWebEngineView *webView = new QWebEngineView();
    CustomWebPage *page = new CustomWebPage(webView);
    webView->setPage(page);
    webView->setUrl(QUrl("https://duckduckgo.com"));
    
    connect(webView, &QWebEngineView::urlChanged, this, &BrowserWindow::updateUrlBar);
    connect(webView, &QWebEngineView::titleChanged, this, &BrowserWindow::updateTabTitle);

    QTabWidget *tabWidget = centralWidget()->findChild<QTabWidget*>();
    if (tabWidget) {
        tabWidget->addTab(webView, "DuckDuckGo");
    }
    webView->show();

    return webView;
}



void BrowserWindow::updateTabTitle(const QString &title) {
    QWebEngineView *currentWebView = qobject_cast<QWebEngineView*>(sender());
    if (currentWebView) {
        int index = tabWidget->indexOf(currentWebView);
        if (index != -1) {
            tabWidget->setTabText(index, title);
        }
    }
}
