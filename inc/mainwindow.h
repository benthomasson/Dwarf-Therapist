#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

class DFInstance;
class DwarfModel;
class Dwarf;
class OptionsMenu;
class AboutDialog;
class CustomProfession;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

	QSettings *get_settings() {return m_settings;}

    public slots:
        void connect_to_df();
		void read_dwarves();
		void scan_memory();
		
		//settings
		void show_toolbutton_text(bool);
		void set_group_by(int);
		void set_single_click_labor_changes(bool);
		void set_allow_grid_focus(bool);

		// dialogs
		void show_about();
		void add_custom_profession();
		void open_options_menu();

		void new_pending_changes(int);
		void list_pending();
		void draw_professions();
		void draw_grid_context_menu(const QPoint &);
		void draw_custom_profession_context_menu(const QPoint &);
		void edit_custom_profession(QListWidgetItem*);
		void edit_custom_profession();
		void delete_custom_profession();
		void import_existing_professions();
		
		void check_latest_version();
		void version_check_finished(bool error);
		
private:
    Ui::MainWindow *ui;
    DFInstance *m_df;
	QLabel *m_lbl_status;
	QSettings *m_settings;
	DwarfModel *m_model;
	QSortFilterProxyModel *m_proxy;
	OptionsMenu *m_options_menu;
	AboutDialog *m_about_dialog;
	QVector<CustomProfession*> m_custom_professions;
	CustomProfession *m_temp_cp;
	QHttp *m_http;
	bool m_reading_settings;

	void closeEvent(QCloseEvent *evt); // override;

	void read_settings();
	void write_settings();

	CustomProfession *get_custom_profession(QString);

    private slots:
        void set_interface_enabled(bool);
		void color_changed(const QString &, const QColor &);
		void apply_custom_profession();
		void set_nickname();
		
};

#endif // MAINWINDOW_H