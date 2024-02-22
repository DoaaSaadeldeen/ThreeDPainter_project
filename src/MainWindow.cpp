#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <Mainwindow.h>
#include "ui_MainWindow.h"
#include <vtkSphereSource.h>
#include <vtkCylinderSource.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkQtTableView.h>
#include <vtkVersion.h>
#include <vtkTransform.h>
#include <vtkRendererCollection.h>
#include <vtkActorCollection.h>
#include <QMessageBox>
#include <sstream>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#include <vtkPyramid.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkUnstructuredGrid.h>
#include <QRadioButton>

bool red = 0, blue = 0, yellow = 0;
MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New())
{
    ui->setupUi(this);
	// Set up the rendering
	mRenderWindow->AddRenderer(mRenderer);
	mRenderWindow->SetInteractor(mInteractor);
	ui->openGLWidget->setRenderWindow(mRenderWindow);
	mInteractor->SetInteractorStyle(mInteractorStyle);
	mInteractor->Initialize();

	// Set the UI connections//        signal                                     slot
	QObject::connect(ui->drawButton, &QPushButton::clicked, this, &MainWindow::onDrawButtonClick);
    QObject::connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onclearButtonClick);
	connect(ui->redButton, &QRadioButton::pressed, this, &MainWindow::changeColorToRed);
	connect(ui->blueButton, &QRadioButton::pressed, this, &MainWindow::changeColorToBlue);
	connect(ui->yellowButton, &QRadioButton::pressed, this, &MainWindow::changeColorToYellow);
	
}

MainWindow::~MainWindow()
{
    delete ui;
}

vtkSmartPointer<vtkActor> MainWindow::Fun()
{
	onclearButtonClick();
	vtkNew<vtkDataSetMapper> shapeMapper;
	QString type = ui->shapeListWidget->selectedItems().first()->text();
	if (type == "Cube") {
		shapeMapper->SetInputConnection(vtkNew<vtkCubeSource>()->GetOutputPort());
	}
	else if (type == "Sphere") {
		vtkNew<vtkSphereSource>sphere;
		sphere->SetThetaResolution(BestResolution);
		sphere->SetPhiResolution(BestResolution);
		shapeMapper->SetInputConnection(sphere->GetOutputPort());
	}
	else if (type == "HemiSphere") {
		vtkNew<vtkSphereSource>sphere;
		sphere->SetThetaResolution(BestResolution);
		sphere->SetPhiResolution(BestResolution);
		sphere->SetEndTheta(180);
		shapeMapper->SetInputConnection(sphere->GetOutputPort());
	}
	else if (type == "Cone") {
		vtkNew<vtkConeSource>cone;
		cone->SetResolution(BestResolution);
		shapeMapper->SetInputConnection(cone->GetOutputPort());
	}
	else if (type == "Pyramid") {
		vtkNew<vtkConeSource>cone;
		cone->SetResolution(4);
		cone->SetRadius(0.7);
		shapeMapper->SetInputConnection(cone->GetOutputPort());
	}
	else if (type == "Cylinder") {
		vtkNew<vtkCylinderSource> cylinder;
		cylinder->SetResolution(BestResolution);
		shapeMapper->SetInputConnection(cylinder->GetOutputPort());
	}
	else if (type == "Tube") {
		vtkNew<vtkCylinderSource> cylinder;
		cylinder->SetResolution(BestResolution);
		cylinder->SetCapping(true);
		shapeMapper->SetInputConnection(cylinder->GetOutputPort());
	}
	else if (type == "Curved Cylinder") {
		vtkNew<vtkCylinderSource> cylinder;
		cylinder->SetResolution(BestResolution);
		cylinder->SetRadius(4);
		shapeMapper->SetInputConnection(cylinder->GetOutputPort());
	}

	shape = vtkNew<vtkActor>();
	shape->SetMapper(shapeMapper);
	if (red == true){
		shape->GetProperty()->SetColor(255, 0, 0);
		mRenderer->SetBackground(25, 25, 25);
	}
	else if (blue == true) {
		shape->GetProperty()->SetColor(0, 0, 255);
		mRenderer->SetBackground(0, 128, 254);
	}
	else if (yellow == true) {
		shape->GetProperty()->SetColor(255, 255, 0);
		mRenderer->SetBackground(104, 104, 104);
	}


	// set shape opacity
	int opacity=ui->opacityTextEdit->toPlainText().toInt();
	opacity = (opacity == 0) ? 10 : opacity;
	if (opacity > 100)
	{
		opacity = 100;
		ui->opacityTextEdit->setText(std::to_string(opacity).c_str());
	}
	shape->GetProperty()->SetOpacity(opacity / 100.0);

	return shape;
}
void MainWindow::changeColorToRed()
{
		red = 1, blue = 0, yellow = 0;

}
void MainWindow::changeColorToBlue()
{
		red = 0, blue = 1, yellow = 0;
}
void MainWindow::changeColorToYellow()
{
	red = 0, blue = 0, yellow = 1; 
}
void MainWindow::onDrawButtonClick()
{
	if (ui->shapeListWidget->selectedItems().isEmpty() !=true)
	{
		// Add the shape actor to the OpenGL
		mRenderer->AddActor(Fun());
		mRenderer->ResetCamera();
		mRenderWindow->Render();
		
	}
	else {
		QMessageBox::warning(this, "Warning", "You have to choose the shape first to be shown.");
		return;
	}
	
}
void MainWindow::onclearButtonClick() {
	while (mRenderer->GetActors()->GetNumberOfItems())
	{
		auto lastActor = mRenderer->GetActors()->GetLastActor();
		mRenderer->RemoveActor(lastActor);
	}
	mRenderWindow->Render();
}