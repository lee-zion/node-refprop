# refprop

Node.js interface to <a href="https://www.nist.gov/srd/refprop">NIST REFPROP</a>.

REFPROP-headers
https://github.com/CoolProp/REFPROP-headers

REFPROP-Wrapper v10.0 for Python
https://nbviewer.jupyter.org/github/usnistgov/REFPROP-wrappers/blob/master/wrappers/python/notebooks/Tutorial.ipynb

REFPROP v10.0 API
https://refprop-docs.readthedocs.io/en/latest/DLL/high_level.html

Wrapping REFPROP via Coolprop
http://www.coolprop.org/coolprop/wrappers/StaticLibrary/index.html#static-library
/examples/Coolprop C++ interface

# [Install]

Windows: npm install -g node-gyp
python 2.7 (2019/10/13, Yet no support for python 3.x.x)
npm install -g --production windows-build-tools
macOS: xcode-select --install (Xcode Command Line Tools)
npm install -g node-gyp
python 2.7(default installed), 3.5, 3.5 or 3.7

Reference: https://nhj12311.tistory.com/29

# [Development]

Source codes are located at src directory
binding.gyp

# [Build]

# [Testing]

Testing codes for build result in Javascript within mocha

# [Deployment]
