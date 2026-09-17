import numpy as np
import PyIRI.sh_library as sh

#coordinates for wallops
LAT = 37.9402
LON = -75.4664

YEAR, MONTH, DAY = 2026, 5, 15

LOCAL_HOUR = 5.0
UTC_OFFSET_HOURS = -4.0   # EDT = UTC-4
UT_HOUR = LOCAL_HOUR - UTC_OFFSET_HOURS


F107 = 150 #seems like average, will investigate further


ALT_MIN = 100 #minimum altitude
ALT_MAX = 200  #max altitude
ALT_STEP = 1 #"fidelity"

aalt = np.arange(ALT_MIN, ALT_MAX, ALT_STEP)

*_, density_profile = sh.IRI_density_1day( #*_ to absorb uneeded return values, all we need right now is denstiy profile
    YEAR, MONTH, DAY, UT_HOUR, LON, LAT, aalt, F107,
    coeff_dir=None,
    foF2_coeff='URSI',
    hmF2_model='SHU2015',
    coord='GEO',
    old_output=False)

i = ALT_MIN
for density in density_profile[0]:
	print("electron density at " + str(i) + "km: " +  str(density[0]))
	i += 1

