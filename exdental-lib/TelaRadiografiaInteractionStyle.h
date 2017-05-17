#pragma once

#include "vtkInteractorStyleTrackballCamera.h"

// Motion flags

#define MYIS_WINDOW_LEVEL 1024
#define MYIS_PICK         1025
#define MYIS_SLICE        1026

// Style flags

#define MYIS_IMAGE2D 2
#define MYIS_IMAGE3D 3
#define MYIS_IMAGE_SLICING 4

class vtkImageProperty;
namespace geronimo_impl
{
class TelaRadiografiaInteractionStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static TelaRadiografiaInteractionStyle *New();
	vtkTypeMacro(TelaRadiografiaInteractionStyle, vtkInteractorStyleTrackballCamera);
	void PrintSelf(ostream& os, vtkIndent indent);

	// Description:
	// Some useful information for handling window level
	vtkGetVector2Macro(WindowLevelStartPosition, int);
	vtkGetVector2Macro(WindowLevelCurrentPosition, int);

	// Description:
	// Event bindings controlling the effects of pressing mouse buttons
	// or moving the mouse.
	virtual void OnMouseMove();
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();
	virtual void OnMiddleButtonDown();
	virtual void OnMiddleButtonUp();
	virtual void OnRightButtonDown();
	virtual void OnRightButtonUp();
	virtual void OnMouseWheelForward();
	virtual void OnMouseWheelBackward();

	// Description:
	// Override the "fly-to" (f keypress) for images.
	virtual void OnChar();

	// These methods for the different interactions in different modes
	// are overridden in subclasses to perform the correct motion. Since
	// they might be called from OnTimer, they do not have mouse coord parameters
	// (use interactor's GetEventPosition and GetLastEventPosition)
	virtual void WindowLevel();
	virtual void Pick();
	virtual void Slice();

	// Interaction mode entry points used internally.
	virtual void StartWindowLevel();
	virtual void EndWindowLevel();
	virtual void StartPick();
	virtual void EndPick();
	virtual void StartSlice();
	virtual void EndSlice();

	// Description:
	// Set/Get current mode to 2D or 3D.  The default is 2D.  In 3D mode,
	// it is possible to rotate the camera to view oblique slices.  In Slicing
	// mode, it is possible to slice through the data, but not to generate oblique
	// views by rotating the camera.
	vtkSetClampMacro(InteractionMode, int, MYIS_IMAGE2D, MYIS_IMAGE_SLICING);
	vtkGetMacro(InteractionMode, int);
	void SetInteractionModeToImage2D() {
		this->SetInteractionMode(MYIS_IMAGE2D);
	}
	void SetInteractionModeToImage3D() {
		this->SetInteractionMode(MYIS_IMAGE3D);
	}
	void SetInteractionModeToImageSlicing() {
		this->SetInteractionMode(MYIS_IMAGE_SLICING);
	}

	// Description:
	// Set the orientations that will be used when the X, Y, or Z
	// keys are pressed.  See SetImageOrientation for more information.
	vtkSetVector3Macro(XViewRightVector, double);
	vtkGetVector3Macro(XViewRightVector, double);
	vtkSetVector3Macro(XViewUpVector, double);
	vtkGetVector3Macro(XViewUpVector, double);
	vtkSetVector3Macro(YViewRightVector, double);
	vtkGetVector3Macro(YViewRightVector, double);
	vtkSetVector3Macro(YViewUpVector, double);
	vtkGetVector3Macro(YViewUpVector, double);
	vtkSetVector3Macro(ZViewRightVector, double);
	vtkGetVector3Macro(ZViewRightVector, double);
	vtkSetVector3Macro(ZViewUpVector, double);
	vtkGetVector3Macro(ZViewUpVector, double);

	// Description:
	// Set the view orientation, in terms of the horizontal and
	// vertical directions of the computer screen.  The first
	// vector gives the direction that will correspond to moving
	// horizontally left-to-right across the screen, and the
	// second vector gives the direction that will correspond to
	// moving bottom-to-top up the screen.  This method changes
	// the position of the camera to provide the desired view.
	void SetImageOrientation(const double leftToRight[3],
		const double bottomToTop[3]);

	// Description:
	// Get the current image property, which is set when StartWindowLevel
	// is called immediately before StartWindowLevelEvent is generated.
	// This is the image property of the topmost vtkImageSlice in the
	// renderer or NULL if no image actors are present.
	vtkImageProperty *GetCurrentImageProperty() {
		return this->CurrentImageProperty;
	}

protected:
	TelaRadiografiaInteractionStyle();
	~TelaRadiografiaInteractionStyle();

	void SetCurrentImageToNthImage(int i);

	int WindowLevelStartPosition[2];
	int WindowLevelCurrentPosition[2];
	double WindowLevelInitial[2];
	vtkImageProperty *CurrentImageProperty;

	int InteractionMode;
	double XViewRightVector[3];
	double XViewUpVector[3];
	double YViewRightVector[3];
	double YViewUpVector[3];
	double ZViewRightVector[3];
	double ZViewUpVector[3];

private:
	TelaRadiografiaInteractionStyle(const TelaRadiografiaInteractionStyle&);  // Not implemented.
	void operator=(const TelaRadiografiaInteractionStyle&);  // Not implemented.

public:
	void SetWindowLevelStartPosition(int w, int l)
	{
		WindowLevelCurrentPosition[0] = w;
		WindowLevelCurrentPosition[1] = l;
		WindowLevelStartPosition[0] = w;
		WindowLevelStartPosition[1] = l;
	}
};


 }