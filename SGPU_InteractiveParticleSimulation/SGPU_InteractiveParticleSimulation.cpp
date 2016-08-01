#include "SGPU_InteractiveParticleSimulation.h"
#include <QColorDialog>
#include <qtimer.h>
#include "QViewport.h"

SGPU_InteractiveParticleSimulation::SGPU_InteractiveParticleSimulation(QWidget *parent) : QMainWindow(parent) {
    this->ui.setupUi(this);
}

SGPU_InteractiveParticleSimulation::~SGPU_InteractiveParticleSimulation() {}

void SGPU_InteractiveParticleSimulation::onUpdate() {
    std::cout << "Update!" << std::endl;

    //--------------------------------------------------------------------------
    // The ui member of this class holds all of the user interface components 
    // from the demo. To acces the value of a Qt SpinBox, the value() function 
    // is used.
    //
    // TODO: Get all simulation properties from the main window tool panel.
    //--------------------------------------------------------------------------
    float particleSize = this->ui.particleSize->value();

    //--------------------------------------------------------------------------
    // The value set from the user interface can then be transfered through
    // the viewport to the particle system.
    //
    // TODO: Update the simulation.
    //--------------------------------------------------------------------------
    this->ui.viewport->setParticleSize(particleSize);
}

void SGPU_InteractiveParticleSimulation::onStart() {
	std::cout << "Start!" << std::endl;
	this->ui.viewport->startButton();
}

void SGPU_InteractiveParticleSimulation::onStop() {
	std::cout << "Stop!" << std::endl;
	this->ui.viewport->stopButton();
}

void SGPU_InteractiveParticleSimulation::onColorButton() {
    QColor color = QColorDialog::getColor(Qt::blue, this);
	float colorR = color.redF();
	float colorG = color.greenF();
	float colorB = color.blueF();
    //--------------------------------------------------------------------------
    // TODO: Update the particle color.
    //--------------------------------------------------------------------------
    if ( color.isValid() ) {
		this->ui.viewport->setColor(colorR, colorG, colorB);
    }
}
