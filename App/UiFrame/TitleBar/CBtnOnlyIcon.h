#pragma once

#include <QPushButton>

typedef enum BtnOnlyIconType
{
    em_normal = 0x00,
    em_active = 0x01,
    em_hover  = 0x02,
} IconType;

class QIcon;
class CBtnOnlyIcon : public QPushButton
{
public:
    explicit CBtnOnlyIcon(QWidget *parent = nullptr);
    virtual ~CBtnOnlyIcon();
    void AddActiveHover(const QString &path);
    void AddNormalHover(const QString &path);
    void AddActive(const QString &path);
    void AddNormal(const QString &path);
    void SetIconsSize(const QSize &);

protected:
    void paintEvent(QPaintEvent *event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    void leaveEvent(QEvent *event) override;

private Q_SLOTS:
    void Slot_Clicked();

private:
    QPixmap m_NormalIcon;
    QPixmap m_NormalHoverIcon;
    QPixmap m_ActiveIcon;
    QPixmap m_ActiveHoverIcon;
    QSize m_IconSize;
    bool m_blChanged;
    unsigned int m_emState;
};
