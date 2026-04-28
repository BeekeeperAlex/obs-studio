#pragma once

#include "OAuth.hpp"

#include <json11.hpp>

#include <utility>
#include <vector>

#include <QDockWidget>
#include <QEvent>
#include <QPointer>
#include <QTimer>

class TwitchAuth : public OAuthStreamKey {
	Q_OBJECT
	bool uiLoaded = false;
	bool deferredDockVisibilityRestore = false;
	bool eventFilterInstalled = false;
	std::vector<std::pair<QPointer<QDockWidget>, bool>> deferredDocks;

	std::string name;
	std::string uuid;

	virtual bool RetryLogin() override;

	virtual void SaveInternal() override;
	virtual bool LoadInternal() override;

	bool MakeApiRequest(const char *path, json11::Json &json_out);
	bool GetChannelInfo();

	virtual void LoadUI() override;
	bool eventFilter(QObject *obj, QEvent *event) override;
	void DeferDockVisibility(QDockWidget *dock);
	void HideDeferredDocks();
	void InstallDockVisibilityRestore();
	void RestoreDeferredDockVisibility();
	bool ShouldHideTwitchDocksOnStartup();

public:
	TwitchAuth(const Def &d);
	~TwitchAuth();

	static std::shared_ptr<Auth> Login(QWidget *parent, const std::string &service_name);

	QTimer uiLoadTimer;

public slots:
	void TryLoadSecondaryUIPanes();
	void LoadSecondaryUIPanes();
};
