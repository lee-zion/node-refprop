#include <node.h>
#include <iostream>
#include <windows.h>
#define REFPROP_IMPLEMENTATION
#include "REFPROP_lib.h"
#undef REFPROP_IMPLEMENTATION
#include "node-refprop.h"

using namespace v8;
using namespace node;

RefpropContext* RefpropContext::_instance = NULL;

// singleton pattern
RefpropContext* RefpropContext::instance(v8::Isolate* iso) {
	if (!_instance)   // Only allow one instance of class to be generated.
		_instance = new RefpropContext(iso);
	return _instance;
}

RefpropContext::RefpropContext(v8::Isolate* iso) {
	// std::string path = ".\\..\\REFPROP";
	std::string path = "C:\\Users\\DELL\\Documents\\GitHub\\node-refprop\\REFPROP";
	std::string DLL_name = "refprop.DLL";
	std::string err;
	bool loaded_REFPROP = load_REFPROP(err, path, DLL_name);
	// printf("Loaded refprop (in main.cpp): %s @ address %zu\n", loaded_REFPROP ? "true" : "false", REFPROP_address());
    // if (!loaded_REFPROP){
    //     return EXIT_FAILURE;
    // }

	// this->RefpropDllInstance = REFPROP_address();
	// if (NULL == this->RefpropDllInstance) {
	// 	iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Failed to load refprop.dll")));
	// 	return;
	// }

	printf("path: %s\n", path);
	printf("err: %s\n", err);
	printf("bool: %d\n", loaded_REFPROP);
	SETPATHdll(const_cast<char*>(path.c_str()), 400);
    int ierr = 0;
    printf("\nSETFLUID? %d\n", ierr);
    SETFLUIDSdll("WATER", ierr, 1000);
    printf("\nSETFLUID? %d\n", ierr);

    // int ierr = 0, nc = 1;
    // char herr[255], hfld[10000] = "R32.FLD", hhmx[255] = "HMX.BNC", href[255] = "DEF";
    // SETUPdll(nc,hfld,hhmx,href,ierr,herr,10000,255,3,255);
    // if (ierr > 0) {
	// 	printf("This ierr: %d herr: %s\n", ierr, herr);
	// 	printf("nc: %d hfld: %s hhmx: %s href: %s\n", nc, hfld, hhmx, href);
	// }
    // {
    //     int ierr = 0;
    //     char herr[255];
    //     double z[20] = {1.0}, x[20] = {1.0}, y[20] = {1.0}, T= 300, p = 101.325, d = -1, dl = -1, dv = -1, h = -1, s = -1, u = -1, cp = -1, cv = -1, q = -1, w = -1;
    //     TPFLSHdll(T, p, z, d, dl, dv, x, y, h,s,u,cp,cv,w,q,ierr,herr,255);
    //     if (ierr > 0) printf("Other ierr: %ld herr: %s\n", ierr, herr);
    //     printf("Other d: %g mol/L\n", d);
    // }
	
	// int ierr = 0, nc = 1;
    // char herr[255], hfld[10000] = "AMMONIA|WATER", hhmx[255] = "HMX.BNC", href[4] = "DEF";
    // SETUPdll(nc,hfld,hhmx,href,ierr,herr,10000,255,3,255);
    // if (ierr > 0) {
	// 	printf("This ierr: %d herr: %s\n", ierr, herr);
	// 	printf("nc: %d hfld: %s hhmx: %s href: %s\n", nc, hfld, hhmx, href);
	// }
    // {
    //     int ierr = 0;
    //     char herr[255];
    //     double z[20] = {1.0}, x[20] = {1.0}, y[20] = {1.0}, T= 300, p = 101.325, d = -1, dl = -1, dv = -1, h = -1, s = -1, u = -1, cp = -1, cv = -1, q = -1, w = -1;
    //     TPFLSHdll(T, p, z, d, dl, dv, x, y, h,s,u,cp,cv,w,q,ierr,herr,255);
    //     if (ierr > 0) printf("This ierr: %d herr: %s\n", ierr, herr);
    //     printf("This d: %g mol/L\n", d);
        // {
        //     double T = 293.15; double z[20] = { 0.20209999999999995, 0.7979}; int kph = 1;
        //     double P, rhol, rhov;
        //     double x[20], y[20];
        //     int ierr; char herr[255];
        //     SATTdll(T, z, kph, P, rhol, rhov, x, y, ierr, herr, 255);
        //     printf("This p: %g mol/L\n", p);
        // }
    // }
}

// void setFluid(const FunctionCallbackInfo<Value>& args) {
// 	Isolate* iso = args.GetIsolate();

// 	RefpropContext* rp = RefpropContext::instance(iso);

// 	// now we do error checking to ensure we can pop out the requestedFluid argument
//     if (args.Length() < 1) {
//         iso->ThrowException(Exception::TypeError(
//             String::NewFromUtf8(iso, "Must specify the fluid type when creating a refprop context")));
//     }

//     // now pull out the requestedFluid and cram it into a c-style string
// 	String::Utf8Value requestedFluid(args[0]->ToString());
// 	rp->setFluid(*requestedFluid, iso);
// 	args.GetReturnValue().Set(Undefined(iso));
// }

// void setPPF(const FunctionCallbackInfo<Value>& args) {
// 	Isolate* iso = args.GetIsolate();

// 	RefpropContext* rp = RefpropContext::instance(iso);
// 	// now we do error checking to ensure we can pop out the requestedFluid argument
//     if (args.Length() < 1) {
//         iso->ThrowException(Exception::TypeError(
//             String::NewFromUtf8(iso, "Must specify the fluid type when creating a refprop context")));
//     }

//     // now pull out the requestedFluid and cram it into a c-style string
// 	String::Utf8Value requestedFluid(args[0]->ToString());
// 	rp->setPPF(*requestedFluid, iso);
// 	args.GetReturnValue().Set(Undefined(iso));
// }

void getFluid(const FunctionCallbackInfo<Value>& args) {
	Isolate* iso = args.GetIsolate();
	RefpropContext* rp = RefpropContext::instance(iso);

	// Local<String> fluid = String::NewFromUtf8(iso, rp->getFluid());
	// args.GetReturnValue().Set(fluid);
}

// void RefpropContext::setFluid(char *requestedFluid, Isolate* iso) {
// 	if (strcmp(this->_fluid, requestedFluid) != 0) {
// 		long i,ierr=0;

// 		char hf[refpropcharlength*ncmax], hrf[lengthofreference],
// 			herr[errormessagelength],hfmix[refpropcharlength];

// 		char *FLD_PATH = "C:\\Users\\DELL\\Documents\\GitHub\\solvicinc\\node-refprop\\REFPROP\\fluids\\";
// 		strcpy(hf,FLD_PATH);
// 		strcpy(hfmix,FLD_PATH);

// 		i=1; 
// 		strcat(hf,requestedFluid);
// 		strcat(hf,".FLD");
// 		strcat(hfmix,"HMX.BNC");
// 		strcpy(hrf,"DEF");
// 		strcpy(herr,"Ok");

// 		this->SETUPdll(i, hf, hfmix, hrf, ierr, herr,refpropcharlength*ncmax,refpropcharlength,lengthofreference,errormessagelength);

// 		if (ierr != 0)
// 			iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Error loading fluid requested fluid!")));
// 		else
// 			strcpy(this->_fluid, requestedFluid);
// 	}
// }

// void RefpropContext::setPPF(char *requestedFluid, Isolate* iso) {
// 	if (strcmp(this->_fluid, requestedFluid) != 0) {
// 		iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Error Just executed setPPF!")));
// 		long i,ierr=0;

// 		char hf[refpropcharlength*ncmax], hrf[lengthofreference], hfiles[lengthofreference],
// 			herr[errormessagelength],hfmix[refpropcharlength*ncmax];

// 		double z[ncmax]={0.0};

// 		char *MIX_PATH = "C:\\Users\\DELL\\Documents\\GitHub\\solvicinc\\node-refprop\\refprop\\mixtures\\";
// 		char *FLD_PATH = "C:\\Users\\DELL\\Documents\\GitHub\\solvicinc\\node-refprop\\refprop\\fluids\\";
// 		strcpy(hf,MIX_PATH);
// 		strcpy(hfmix,FLD_PATH);

// 		//...initialize the program and set the pure fluid component name
// 		i=1; 
// 		strcat(hf,requestedFluid);
// 		strcat(hf,".MIX");
// 		strcat(hfmix,"HMX.BNC");
// 		strcpy(hrf,"DEF");
// 		strcpy(herr,"Ok");

// 		if (ierr != 0)
// 			iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Error loading fluid requested!")));
// 		else
// 			strcpy(this->_fluid, requestedFluid);
// 	}
// }

// char* RefpropContext::getFluid() {
// 	return this->_fluid;
// }

// void statePoint(const FunctionCallbackInfo<Value>& args) {
// 	Isolate *iso = args.GetIsolate();
// 	// there should be at least one and maybe two arguments
// 	// args[0] should be an object with two fields.  the keys should be used to lookup the correct flash function
// 	// args[1] might be an array with strings in it.  the strings represent requested properties
// 	//  - we'll go ahead and always reply with all the flash function properties, but give out whatever else they want

// 	if (args.Length() < 1) {
// 		iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Must provide quantities to establish thermodynamic state")));
// 	}

// 	// get the key/value pairs that establish the thermodynamic state
// 	Local<Object> coords = args[0]->ToObject()->Clone();  // note that the keys are available with coords->GetOwnPropertyNames();
// 	Local<Array> keys = coords->GetOwnPropertyNames();

// 	if (keys->Length() != 2) {
// 		iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Thermodynamic state established by exactly 2 values")));
// 	}

// 	char props[2];
// 	double values[2];

// 	Local<v8::Context> context = iso->GetCurrentContext();

// 	for (int i=0; i < 2; i++) {
// 		String::Utf8Value key(keys->Get(i)->ToString());
// 		props[i] = (*key)[0];
// 		values[i] = coords->Get(keys->Get(i))->NumberValue(context).FromMaybe(0);
// 	}

// 	// grab refprop
// 	RefpropContext* rp = RefpropContext::instance(iso);
// 	ThermoState *state = rp->doFlash(props, values, iso);

// 	args.GetReturnValue().Set(state->toJs(iso));
// }

// RefpropContext::FlashFcn RefpropContext::flashFcnLookup(const char props[2], Isolate* iso) {
// 	int idx[2];

// 	for (int i=0; i < 2; i++) {
// 		char* e = strchr(this->flashString, props[i]);
// 		if (e) {
// 			idx[i] = (int)(e - this->flashString);
// 		}
// 		else {
// 			iso->ThrowException(Exception::TypeError(String::NewFromUtf8(iso, "Provided thermodynamic quantities must be one of TPDHSEQ")));
// 			return NULL;
// 		}
// 	}
// 	return this->flashTable[idx[0]][idx[1]];
// }

void RegisterModule(Local<Object> exports) {
	// syntax for registering functions to the exports object is:
	// NODE_SET_METHOD(exports, "name_of_function", functionPointer);
	// NODE_SET_METHOD(exports, "setFluid", setFluid);
	// NODE_SET_METHOD(exports, "setPPF", setPPF);
	// NODE_SET_METHOD(exports, "statePoint", statePoint);
	NODE_SET_METHOD(exports, "getFluid", getFluid);
}

NODE_MODULE(refprop, RegisterModule)
