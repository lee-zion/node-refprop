var refprop = require("../build/Release/node-refprop");
var should = require("should");
var assert = require("assert");
var fs = require("fs");

describe("refprop 10.0", function() {
  it("should give some hard-coded values", function() {
    refprop.getFluid();
  });
});

describe.skip("refprop 9.1", function() {
  it.skip("should load without error", function() {
    assert.equal(refprop.setFluid("R134A"), undefined);
  });

  it.skip("should throw an error for invalid fluids", function() {
    (function() {
      refprop.setFluid("urine");
    }.should.throw());
  });

  it.skip("should compute single-phase states for pure fluids", function() {
    refprop.setFluid("nitrogen");

    var result = refprop.statePoint({ T: 273.15, P: 101.3e3 });
    result.should.be.Object;
    result.should.have.properties([
      "CP", // Isobaric Heat Capacity [kJ/kgK]
      "CV", // Isochoric Heat Capacity [kJ/kgK]
      "D", // Density [kg/m3]
      "DL", //
      "DV", //
      "E", // Internal Energy [kJ/kg]
      "H", // Enthalpy [kJ/kg]
      "P", // Pressure [kPa]
      "Q", //
      "S", // Entropy [kJ/kgK]
      "T", // Temperature [K]
      "W", // Speed of Sound [m/s]
      "X", //
      "k", //
      "mu" //
    ]);

    result.T.should.be.eql(273.15);
    result.P.should.be.eql(101.3e3);
    result.H.should.be.approximately(283.23e3, 0.01e3);
    result.D.should.be.approximately(1.2501, 0.0001);
    result.S.should.be.approximately(6.7442e3, 0.1);
  });

  it.skip("should compute two-phase states for pure fluids", function() {
    refprop.setFluid("isobutan");

    var result = refprop.statePoint({ T: 220, Q: 0.5 });
    result.should.be.Object;
    result.should.have.properties([
      "CP",
      "CV",
      "D",
      "DL",
      "DV",
      "E",
      "H",
      "P",
      "Q",
      "S",
      "T",
      "W",
      "X",
      "CPL",
      "CPV",
      "kL",
      "kV",
      "CVL",
      "CVV",
      "muL",
      "muV",
      "sigma"
    ]);

    result.T.should.be.eql(220);
    result.P.should.be.approximately(14.023e3, 0.001e3);
    result.H.should.be.approximately(284.9e3, 0.01e3);
    result.D.should.be.approximately(0.89931, 0.00001);
    result.S.should.be.approximately(1.4422e3, 0.0001e3);
    result.CPL.should.be.approximately(2.0413e3, 0.0001e3);
    result.CPV.should.be.approximately(1.3296e3, 0.0001e3);
    result.kL.should.be.approximately(0.12056, 0.00001);
    result.kV.should.be.approximately(9.6201e-3, 0.0001);
  });

  it.skip("should load without error", function() {
    refprop.setPPF("R410A");
    console.log(typeof refprop);
    console.log(refprop);
  });

  it.skip("should compute states for 500 times", function(done) {
    var resultArr = [];
    for (let i = 0; i < 500; i++) {
      refprop.setFluid("nitrogen");
      var result = refprop.statePoint({ T: 50.15 + i * 0.1, P: 101.3e3 });
      result.should.be.Object;
      result.should.have.properties([
        "CP", // Isobaric Heat Capacity [kJ/kgK]
        "CV", // Isochoric Heat Capacity [kJ/kgK]
        "D", // Density [kg/m3]
        "DL", // Density (Liquid)
        "DV", // Density (Vapor)
        "E", // Internal Energy [kJ/kg]
        "H", // Enthalpy [kJ/kg]
        "P", // Pressure [kPa]
        "Q", // Vapor Quality [mol/mol]
        "S", // Entropy [kJ/kgK]
        "T", // Temperature [K]
        "W", // Speed of Sound [m/s]
        "X", //
        "k", // Thermal Conductivity
        "mu" // Viscosity
      ]);
      resultArr.push(JSON.stringify(result));
    }
    fs.writeFile("outputs.txt", resultArr, "utf-8", done);
  });

  it.skip("should compute states for pre-defined mixtures", function() {
    refprop.setPPF("R410A");
    var result = refprop.statePoint({ T: 273.15, P: 101.3e3 });
    result.should.be.Object;
    result.should.have.properties([
      "CP",
      "CV",
      "D",
      "DL",
      "DV",
      "E",
      "H",
      "P",
      "Q",
      "S",
      "T",
      "W",
      "X",
      "k",
      "mu"
    ]);

    result.T.should.be.eql(273.15);
    result.P.should.be.eql(101.3e3);
    result.H.should.be.approximately(439.57e3, 0.01e3);
    result.D.should.be.approximately(3.2981, 0.0001);
    result.S.should.be.approximately(2.0983e3, 0.1);
  });

  it.skip("should compute states for custom mixtures", function() {});
});
