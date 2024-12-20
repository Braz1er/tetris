#pragma once

#include <QWidget>
#include <QLabel>

class ScorePanel : public QWidget {
Q_OBJECT

public:
    ScorePanel(QWidget *parent = nullptr);

    void setScore(int score);
    void setLevel(int level);

private:
    QLabel *scoreLabel;
    QLabel *levelLabel;
};