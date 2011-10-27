#ifndef NOTHINGPLAYINGWIDGET_H
#define NOTHINGPLAYINGWIDGET_H

#include <QWidget>

#include "lib/unicorn/StylableWidget.h"

namespace lastfm { class User; }
namespace unicorn { class Session; }


class NothingPlayingWidget : public StylableWidget
{
    Q_OBJECT
private:
    struct
    {
        class QLabel* top;
        class QuickStartWidget* quickStart;
        class QLabel* split;
        class QLabel* bottom;

        StylableWidget* players;
        class QPushButton* itunes;
        class QPushButton* wmp;
        class QPushButton* winamp;
        class QPushButton* foobar;
    } ui;

public:
    explicit NothingPlayingWidget( QWidget* parent = 0 );

private:
    void setUser( const lastfm::User& user );

private slots:
    void onSessionChanged( unicorn::Session* session );

    void oniTunesClicked();

};

#endif // NOTHINGPLAYINGWIDGET_H