#pragma once

// Our includes
#include "AbstractPainterPathModel.h"
#include "TextModel.h"
#include "cwLength.h"

// Qt includes
#include <QRectF>
#include <QColor>
#include <QFont>
#include <QObjectBindableProperty>
#include <QQmlEngine>
#include <QMatrix4x4>

namespace cwSketch {

class FixedGridModel : public AbstractPainterPathModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool gridVisible READ gridVisible WRITE setGridVisible NOTIFY gridVisibleChanged BINDABLE bindableGridVisible)
    Q_PROPERTY(double lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged BINDABLE bindableLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged BINDABLE bindableLineColor)
    Q_PROPERTY(cwLength* gridInterval READ gridInterval CONSTANT)

    Q_PROPERTY(QMatrix4x4 mapMatrix READ mapMatrix WRITE setMapMatrix NOTIFY mapMatrixChanged BINDABLE bindableMapMatrix)
    Q_PROPERTY(QRectF viewport READ viewport WRITE setViewport NOTIFY viewportChanged BINDABLE bindableViewport)
    Q_PROPERTY(QPointF origin READ origin WRITE setOrigin NOTIFY originChanged BINDABLE bindableOrigin)

    Q_PROPERTY(bool labelVisible READ labelVisible WRITE setLabelVisible NOTIFY labelVisibleChanged BINDABLE bindableLabelVisible)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged BINDABLE bindableLabelColor)
    Q_PROPERTY(QFont labelFont READ labelFont WRITE setLabelFont NOTIFY labelFontChanged BINDABLE bindableLabelFont)
    Q_PROPERTY(double hiddenInterval READ hiddenInterval WRITE setHiddenInterval NOTIFY hiddenIntervalChanged BINDABLE bindableHiddenInterval)
    Q_PROPERTY(QList<QRectF> labelMasks READ labelMasks WRITE setLabelMasks NOTIFY labelMasksChanged BINDABLE bindableLabelMasks)

    Q_PROPERTY(double labelBackgroundMargin READ labelBackgroundMargin WRITE setLabelBackgroundMargin NOTIFY labelBackgroundMarginChanged BINDABLE bindableLabelBackgroundMargin)
    Q_PROPERTY(QColor labelBackgroundColor READ labelBackgroundColor WRITE setLabelBackgroundColor NOTIFY labelBackgroundColorChanged BINDABLE bindableLabelBackgroundColor)
    Q_PROPERTY(TextModel* textModel READ textModel CONSTANT)

    Q_PROPERTY(double labelScale READ labelScale WRITE setLabelScale NOTIFY labelScaleChanged BINDABLE bindableLabelScale)

    Q_PROPERTY(double gridIntervalPixels READ gridIntervalPixels NOTIFY gridIntervalPixelsChanged BINDABLE bindableGridIntervalPixels)
    Q_PROPERTY(QSizeF maxLabelSizePixels READ maxLabelSizePixels NOTIFY maxLabelSizePixelsChanged BINDABLE bindableMaxLabelSizePixels)

    Q_PROPERTY(double gridZ READ gridZ WRITE setGridZ NOTIFY gridZChanged BINDABLE bindableGridZ)
    Q_PROPERTY(double labelBackgroundZ READ labelBackgroundZ WRITE setLabelBackgroundZ NOTIFY labelBackgroundZChanged BINDABLE bindableLabelBackgroundZ)
    Q_PROPERTY(double labelZ READ labelZ WRITE setLabelZ NOTIFY labelZChanged BINDABLE bindableLabelZ)


public:
    enum Index {
        GridLineIndex = 0,
        LabelBackgroundIndex = 1
    };

    explicit FixedGridModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    // Grid properties
    bool gridVisible() const { return m_gridVisible; }
    void setGridVisible(bool visible) { m_gridVisible = visible; }
    QBindable<bool> bindableGridVisible() { return &m_gridVisible; }

    double lineWidth() const { return m_lineWidth; }
    void setLineWidth(double width) { m_lineWidth = width; }
    QBindable<double> bindableLineWidth() { return &m_lineWidth; }

    QColor lineColor() const { return m_lineColor; }
    void setLineColor(const QColor& color) { m_lineColor = color; }
    QBindable<QColor> bindableLineColor() { return &m_lineColor; }

    cwLength* gridInterval() const { return m_gridInterval; }

    QMatrix4x4 mapMatrix() const { return m_mapMatrix; }
    void setMapMatrix(const QMatrix4x4& mapMatrix) { m_mapMatrix = mapMatrix; }
    QBindable<QMatrix4x4> bindableMapMatrix() { return &m_mapMatrix; }

    QRectF viewport() const { return m_viewport; }
    void setViewport(const QRectF& rect) { m_viewport = rect; }
    QBindable<QRectF> bindableViewport() { return &m_viewport; }

    //In map pixel where (0, 0) is in world coordinates
    QPointF origin() const { return m_origin; }
    void setOrigin(const QPointF& origin) { m_origin = origin; }
    QBindable<QPointF> bindableOrigin() { return &m_origin; }

    // Label properties
    bool labelVisible() const { return m_labelVisible; }
    void setLabelVisible(bool visible) { m_labelVisible = visible; }
    QBindable<bool> bindableLabelVisible() { return &m_labelVisible; }

    QColor labelColor() const { return m_labelColor; }
    void setLabelColor(const QColor& color) { m_labelColor = color; }
    QBindable<QColor> bindableLabelColor() { return &m_labelColor; }

    QFont labelFont() const { return m_labelFont; }
    void setLabelFont(const QFont& font) { m_labelFont = font; }
    QBindable<QFont> bindableLabelFont() { return &m_labelFont; }

    double labelBackgroundMargin() const { return m_labelBackgroundMargin.value(); }
    void setLabelBackgroundMargin(const double& labelBackgroundMargin) { m_labelBackgroundMargin = labelBackgroundMargin; }
    QBindable<double> bindableLabelBackgroundMargin() { return &m_labelBackgroundMargin; }

    QColor labelBackgroundColor() const { return m_labelBackgroundColor.value(); }
    void setLabelBackgroundColor(const QColor& labelBackgroundColor) { m_labelBackgroundColor = labelBackgroundColor; }
    QBindable<QColor> bindableLabelBackgroundColor() { return &m_labelBackgroundColor; }

    double labelScale() const { return m_labelScale; }
    void setLabelScale(double labelScale) { m_labelScale = labelScale; }
    QBindable<double> bindableLabelScale() { return &m_labelScale; }

    //Uses the same map units as gridInterval()
    //Ignores grid lines at this interval. This is useful for composing other grid model together
    double hiddenInterval() const { return m_hiddenInterval.value(); }
    void setHiddenInterval(const double& hiddenInterval) { m_hiddenInterval = hiddenInterval; }
    QBindable<double> bindableHiddenInterval() { return &m_hiddenInterval; }

    double gridIntervalPixels() const { return m_gridIntervalPixels.value(); }
    QBindable<double> bindableGridIntervalPixels() const { return &m_gridIntervalPixels; }

    QSizeF maxLabelSizePixels() const { return m_maxLabelSizePixels.value(); }
    QBindable<QSizeF> bindableMaxLabelSizePixels() const { return &m_maxLabelSizePixels; }

    TextModel *textModel() const { return m_textModel; }

    double gridZ() const { return m_gridZ.value(); }
    void setGridZ(const double& gridZ) { m_gridZ = gridZ; }
    QBindable<double> bindableGridZ() { return &m_gridZ; }

    double labelBackgroundZ() const { return m_labelBackgroundZ.value(); }
    void setLabelBackgroundZ(const double& labelBackgroundZ) { m_labelBackgroundZ = labelBackgroundZ; }
    QBindable<double> bindableLabelBackgroundZ() { return &m_labelBackgroundZ; }

    double labelZ() const { return m_labelZ.value(); }
    void setLabelZ(const double& labelZ) { m_labelZ = labelZ; }
    QBindable<double> bindableLabelZ() { return &m_labelZ; }


    QList<QRectF> labelMasks() const { return m_labelMasks.value(); }
    void setLabelMasks(const QList<QRectF>& labelMasks) { m_labelMasks = labelMasks; }
    QBindable<QList<QRectF>> bindableLabelMasks() { return &m_labelMasks; }


signals:
    void gridVisibleChanged();
    void lineWidthChanged();
    void lineColorChanged();
    void mapMatrixChanged();
    void viewportChanged();
    void originChanged();
    void labelVisibleChanged();
    void labelColorChanged();
    void labelFontChanged();
    void labelScaleChanged();
    void labelBackgroundMarginChanged();
    void labelBackgroundColorChanged();
    void gridIntervalPixelsChanged();
    void hiddenIntervalChanged();
    void maxLabelSizePixelsChanged();
    void gridZChanged();
    void labelBackgroundZChanged();
    void labelZChanged();
    void labelMasksChanged();

protected:
    Path path(const QModelIndex& index) const override;

private:
    void updatePaths();

    // storage
    cwLength* m_gridInterval;

    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, bool, m_gridVisible, true, &FixedGridModel::gridVisibleChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_lineWidth, 1.0, &FixedGridModel::lineWidthChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QColor, m_lineColor, QColor(0xCC, 0xCC, 0xCC), &FixedGridModel::lineColorChanged)

    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QMatrix4x4, m_mapMatrix, &FixedGridModel::mapMatrixChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QRectF, m_viewport, QRectF(), &FixedGridModel::viewportChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QPointF, m_origin, QPointF(), &FixedGridModel::originChanged);

    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, bool, m_labelVisible, true, &FixedGridModel::labelVisibleChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QColor, m_labelColor, QColor(0x88, 0x88, 0x88), &FixedGridModel::labelColorChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QFont, m_labelFont, QFont(), &FixedGridModel::labelFontChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_labelBackgroundMargin, 2.0, &FixedGridModel::labelBackgroundMarginChanged);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QColor, m_labelBackgroundColor, Qt::white, &FixedGridModel::labelBackgroundColorChanged);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_labelScale, 1.0, &FixedGridModel::labelScaleChanged);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_hiddenInterval, 0.0, &FixedGridModel::hiddenIntervalChanged);

    //Any rectangles in this list, will hide labels in the grid. This is useful for hidding origin labels
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QList<QRectF>, m_labelMasks, QList<QRectF>(), &FixedGridModel::labelMasksChanged);

    //z values for the grid, for ordering
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_gridZ, 0.0, &FixedGridModel::gridZChanged);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_labelBackgroundZ, 0.0, &FixedGridModel::labelBackgroundZChanged);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_labelZ, 0.0, &FixedGridModel::labelZChanged);

    //Readonly properties
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, double, m_gridIntervalPixels, 0.0, &FixedGridModel::gridIntervalPixelsChanged);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, QSizeF, m_maxLabelSizePixels, QSizeF(), &FixedGridModel::maxLabelSizePixelsChanged);


    struct GridLine {
        double position; //Position on the map
        double value; //The cave distance label

        bool operator==(const GridLine& other) const {
            return position == other.position
                   && value == other.value;
        }

        bool operator!=(const GridLine& other) const {
            return !(*this == other);
        }
    };

    struct GridLabel {
        QRectF bounds;
        QString text;

        bool operator==(const GridLabel& other) const {
            return bounds == other.bounds
                   && text == other.text;
        }

        bool operator!=(const GridLabel& other) const {
            return !(*this == other);
        }
    };

    //Accessors for computed property
    double gridIntervalLength() const {
        return m_gridInterval->value();
    }
    Q_OBJECT_COMPUTED_PROPERTY(FixedGridModel, double, m_gridIntervalLength, &FixedGridModel::gridIntervalLength);

    //Accessors for computed property
    int gridIntervalUnit() const {
        return m_gridInterval->unit();
    }
    Q_OBJECT_COMPUTED_PROPERTY(FixedGridModel, int, m_gridIntervalUnit, &FixedGridModel::gridIntervalUnit);

    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(FixedGridModel, int, m_size, LabelBackgroundIndex + 1); //Number of paths in the model, will 0, 1, or 2
    // Q_OBJECT_COMPUTED_PROPERTY(FixedGridModel, double, m_gridIntervalLength, &FixedGridModel::gridIntervalLength);

    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QVector<GridLine>, m_xGridLines);
    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QVector<GridLine>, m_yGridLines);
    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QPainterPath, m_gridPath);

    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QVector<GridLabel>, m_gridLabels);
    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QVector<TextModel::TextRow>, m_textRows);

    Q_OBJECT_BINDABLE_PROPERTY(FixedGridModel, QPainterPath, m_labelBackgroundPath);

    QPropertyNotifier m_gridVisibleNotifier;
    QPropertyNotifier m_labelVisibleNotifier;

    //dataChanged updates
    QPropertyNotifier m_lineWidthNotifier;
    QPropertyNotifier m_lineColorNotifier;
    QPropertyNotifier m_labelColorNotifier;
    QPropertyNotifier m_labelFontNotifier;
    QPropertyNotifier m_gridPathNotifier;
    QPropertyNotifier m_labelsPathNotifier;
    QPropertyNotifier m_labelsBackgroundNotifier;
    QPropertyNotifier m_gridLabelsNotifier;


    TextModel *m_textModel = nullptr;

};

} // namespace cwSketch


