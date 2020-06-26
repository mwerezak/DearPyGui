#include "mvPythonModule.h"
#include "mvPythonTranslator.h"
#include "Core/mvApp.h"
#include "mvInterfaces.h"
#include "mvInterfaceRegistry.h"

namespace Marvel {

	static std::map<std::string, mvPythonTranslator> Translators = mvInterfaceRegistry::GetRegistry()->getPythonInterface("sbInput");

	std::map<std::string, mvPythonTranslator> BuildInputsInterface() {

		std::map<std::string, mvPythonTranslator> translators = {

			{"getMousePos", mvPythonTranslator({
			}, false, "Needs documentation")},

			{"isMouseButtonPressed", mvPythonTranslator({
				{mvPythonDataType::Integer, "button"}
			}, false, "Needs documentation")},

			{"isKeyPressed", mvPythonTranslator({
				{mvPythonDataType::Integer, "key"}
			}, false, "Needs documentation")}

		};

		return translators;
	}

	PyObject* getMousePos(PyObject* self, PyObject* args)
	{
		mvMousePos pos = mvApp::GetApp()->getMousePosition();
		PyObject* pvalue = Py_BuildValue("(ff)", pos.x, pos.y);
		return pvalue;
	}

	PyObject* isMouseButtonPressed(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		int button;

		if (!Translators["isMouseButtonPressed"].parse(args, kwargs,__FUNCTION__, &button))
			Py_RETURN_NONE;

		bool pressed = mvApp::GetApp()->isMouseButtonPressed(button);

		PyObject* pvalue = Py_BuildValue("i", pressed);

		return pvalue;
	}

	PyObject* isKeyPressed(PyObject* self, PyObject* args, PyObject* kwargs)
	{
		int key;

		if (!Translators["isMouseButtonPressed"].parse(args, kwargs,__FUNCTION__, &key))
			Py_RETURN_NONE;

		bool pressed = mvApp::GetApp()->isKeyPressed(key);

		PyObject* pvalue = Py_BuildValue("i", pressed);

		return pvalue;
	}

	mvPythonModule* CreateInputInterface()
	{

		auto pyModule = new mvPythonModule("sbInput", {});

		pyModule->addMethodD(getMousePos);
		pyModule->addMethodD(isMouseButtonPressed);
		pyModule->addMethodD(isKeyPressed);

		return pyModule;
	}
}