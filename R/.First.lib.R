.First.lib <- function() {
  require("snpMatrix")
  dyn.load("write_simple.so")
  dyn.load("write_mach.so")
  dyn.load("write_beagle.so")
  dyn.load("write_impute.so")  
}
