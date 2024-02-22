#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkNamedColors.h>
#include <vtkUnstructuredGrid.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
	Ui::MainWindow* ui;
	const int BestResolution = 100;
	vtkSmartPointer<vtkActor> shape;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
	vtkSmartPointer<vtkRenderer> mRenderer;
	vtkSmartPointer<QVTKInteractor> mInteractor;
	vtkSmartPointer<vtkInteractorStyle> mInteractorStyle;
	vtkSmartPointer<vtkActor> Fun();


public slots:
	void onclearButtonClick();
	void onDrawButtonClick();
	void changeColorToRed();
	void changeColorToBlue();
	void changeColorToYellow();

};

#endif // MAINWINDOW_H
