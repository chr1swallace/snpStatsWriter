write.mach <-
function(X,a1,a2,pedfile,markerfile) {
  if (!is(X, "snp.matrix"))
    stop("argument must be a snp.matrix object")
  if(any(a1=="" | is.na(a1) | a2=="" | is.na(a2) | a1==a2))
    stop("alleles must be non-missing characters, and each pair must contain different bases")
  if(length(a1)!=ncol(X))
    stop("require ncol(X) == length(a1) == length(a2)")
  res <- .C("write_mach", X@.Data, as.character(a1), as.character(a2),
            as.character(pedfile), as.integer(nrow(X)),
            as.integer(ncol(X)), rownames(X),
            colnames(X), logical(1))
  error <- res[[9]]
  if (error == 1)
    stop("Couldn't open output file",pedfile)
  cat(paste("M",colnames(X)),file=markerfile,sep="\n")
  return(c(nrow(X), ncol(X)))
}

