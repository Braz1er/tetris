#include "scorepanel.h"
#include <QVBoxLayout>
#include <QPainter>

ScorePanel::ScorePanel(QWidget *parent) : QWidget(parent)
{
    scoreLabel = new QLabel("Score: 0", this);
    levelLabel = new QLabel("Level: 1", this);

    scoreLabel->setAlignment(Qt::AlignHCenter);
    levelLabel->setAlignment(Qt::AlignHCenter);
    scoreLabel->setStyleSheet("font-size: 18px; color: black;");
    levelLabel->setStyleSheet("font-size: 18px; color: black;");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(scoreLabel);
    layout->addWidget(levelLabel);
    layout->addStretch(1);
    setLayout(layout);

    setStyleSheet("background-color: #D3D3D3;");
}

void ScorePanel::setScore(int score)
{
    scoreLabel->setText(QString("Score: %1").arg(score));
}

void ScorePanel::setLevel(int level)
{
    levelLabel->setText(QString("Level: %1").arg(level));
}