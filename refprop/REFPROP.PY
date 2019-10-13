## NIST REFPROP8 Python interface
## Bruce Wernick
## 21 March 2009

from ctypes import *

rp = windll.LoadLibrary("refprop.dll")
SATTdll=rp.SATTdll

# refprop class
class rprop():
  nc=c_long(1)
  ierr=c_long(0)
  herr=create_string_buffer(' ', 255)
  ln1=c_long(1000)
  ln2=c_long(255)
  ln3=c_long(3)
  ln4=c_long(255)
  wmm=c_double()
  ttrp=c_double()
  tnbpt=c_double()
  tc=c_double()
  pc=c_double()
  dc=c_double()
  Zc=c_double()
  acf=c_double()
  dip=c_double()
  Rgas=c_double()
  x=(c_double * 20)()[0]=1
  xliq=(c_double * 20)()
  xvap=(c_double * 20)()
  t=c_double()
  p=c_double()
  Dl=c_double()
  Dv=c_double()
  j=c_long(2) # 1-bubble 2-dew
  def __init__(self,fld='R22'):
    hfld=create_string_buffer('fluids/'+fld+'.fld', 1000)
    hfmix=create_string_buffer('fluids/hmx.bnc', 255)
    hrf=create_string_buffer('DEF', 3)
    rp.SETUPdll(byref(self.nc), byref(hfld), byref(hfmix), byref(hrf), byref(self.ierr), byref(self.herr), self.ln1, self.ln2, self.ln3, self.ln4)
    rp.INFOdll(byref(self.nc), byref(self.wmm), byref(self.ttrp), byref(self.tnbpt), byref(self.tc), byref(self.pc), byref(self.dc), byref(self.Zc), byref(self.acf), byref(self.dip), byref(self.Rgas))
  def SATTdll(self,t,j=2):
    self.t.value=t+273.15
    self.j.value=j
    SATTdll(byref(self.t), self.x, byref(self.j), byref(self.p), byref(self.Dl), byref(self.Dv), self.xliq, self.xvap, byref(self.ierr), byref(self.herr), self.ln2)
    return self.p.value, self.Dl.value*self.wmm.value, self.Dv.value*self.wmm.value



nc=c_long(1)
hfld=create_string_buffer('fluids/R22.fld', 1000)
hfmix=create_string_buffer('fluids/hmx.bnc', 255)
hrf=create_string_buffer('DEF', 3)
ierr=c_long(0)
herr=create_string_buffer(' ', 255)
ln1=c_long(1000)
ln2=c_long(255)
ln3=c_long(3)
ln4=c_long(255)
rp.SETUPdll.restype=None
rp.SETUPdll(byref(nc), byref(hfld), byref(hfmix), byref(hrf), byref(ierr), byref(herr), ln1, ln2, ln3, ln4)

# if ierr.value<>0:
#   print 'ierr ', ierr.value
#   print 'herr ', herr.value

wmm=c_double()
ttrp=c_double()
tnbpt=c_double()
tc=c_double()
pc=c_double()
dc=c_double()
Zc=c_double()
acf=c_double()
dip=c_double()
Rgas=c_double()
rp.INFOdll.restype=None
rp.INFOdll(byref(nc), byref(wmm), byref(ttrp), byref(tnbpt), byref(tc), byref(pc), byref(dc), byref(Zc), byref(acf), byref(dip), byref(Rgas))
# print 'INFOdll'
# print 'wmm   = ', wmm.value
# print 'ttrp  = ', ttrp.value
# print 'tnbpt = ', tnbpt.value
# print 'tc    = ', tc.value
# print 'pc    = ', pc.value
# print 'dc    = ', dc.value
# print 'Zc    = ', Zc.value
# print 'acf   = ', acf.value
# print 'dip   = ', dip.value
# print 'Rgas  = ', Rgas.value

x=(c_double * 20)()
x[0]=1
wm=c_double()
rp.WMOLdll.restype=None
rp.WMOLdll(x, byref(wm))
print 'WMOLdll'
print 'wm   = ', wm.value


rp.CRITPdll.restype=None
rp.CRITPdll(x, byref(tc), byref(pc), byref(dc), byref(ierr), byref(herr), ln2)
print 'CRITPdll'
print 'tc   = ', tc.value
print 'pc   = ', pc.value
print 'dc   = ', dc.value


#Get d from t,p if phase is known:
x=(c_double * 20)()
x[0]=1
t=c_double(278) # K
p=c_double(600) # kPa
d=c_double()
j=c_long(2) # 1-liquid 2-vapor
i=c_long(0)
rp.TPRHOdll.restype=None
rp.TPRHOdll(byref(t), byref(p), x, byref(j), byref(i), byref(d), byref(ierr), byref(herr), ln2)
print ''
print 'TPRHOdll'
print 'density = %0.3f kg/m3' % (d.value*wmm.value)

rp.PRESSdll.restype=None
rp.PRESSdll(byref(t), byref(d), x, byref(p))
print ''
print 'PRESSdll'
print 'temperature = %0.3f K' % t.value
print 'pressure = %0.3f kPa' % p.value


#Saturation routines:
#Third input for Satt and Satp is:  1 - bubble point, 2 - dew point
#Call SATTdll(t, x(1), 1&, p, Dl, Dv, xliq(1), xvap(1), ierr, herr, 255&)
#Call SATPdll(p, x(1), 1&, t, Dl, Dv, xliq(1), xvap(1), ierr, herr, 255&)
x=(c_double * 20)()
x[0]=1
xliq=(c_double * 20)()
xvap=(c_double * 20)()
t=c_double(278) # K
p=c_double() # kPa
Dl=c_double()
Dv=c_double()
j=c_long(2) # 1-bubble 2-dew
i=c_long(0)
rp.SATTdll(byref(t), x, byref(j), byref(p), byref(Dl), byref(Dv), xliq, xvap, byref(ierr), byref(herr), ln2)
print ''
print 'SATTdll'
print 'temperature = %0.3f K' % t.value
print 'pressure = %0.3f kPa' % p.value


print '%10s %10s %10s %10s' % ('Temp', 'Press', 'Dens', 'Dens')
print '%10s %10s %10s %10s' % ('', '', 'liq', 'vap')
print '%10s %10s %10s %10s' % ('degC', 'kPa', 'kg/m\xb3', 'kg/m\xb3')
print '%10s %10s %10s %10s' % (9*'-', 9*'-', 9*'-', 9*'-')
for temp in range(4,6):
  t.value=temp+273.15
  SATTdll(byref(t), x, byref(j), byref(p), byref(Dl), byref(Dv), xliq, xvap, byref(ierr), byref(herr), ln2)
  print '%10.1f %10.3f %10.1f %10.1f' % (temp, p.value, Dl.value*wmm.value, Dv.value*wmm.value)


# sample call using class
rpc=rprop('R22')
print '\nRefProp class'
print 'p=%0.3f dl=%0.1f dv=%0.1f' % rpc.SATTdll(5.0)

