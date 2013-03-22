write.beagle <-
function(X,a1,a2,bp,trait=NULL,gfile,mfile) {
  if (!is(X, "snp.matrix"))
    stop("argument must be a snp.matrix object")
  if(any(a1=="" | is.na(a1) | a2=="" | is.na(a2) | a1==a2))
    stop("alleles must be non-missing characters, and each pair must contain different bases")
  if(length(a1)!=ncol(X))
    stop("require ncol(X) == length(a1) == length(a2)")
  if(length(bp)!=ncol(X))
    stop("require ncol(X) == length(bp)")
  if(!is.null(trait) & length(trait)!=nrow(X))
    stop("require trait (if given) to have length equal to ncol(X)")
  if(!is.null(trait)) {
    r <- range(trait)    
    if(r[1]==0 & r[2]==2) {
      wh <- which(trait==0)
      cat("dropping",length(wh),"individuals with trait==0 (presumed missing)\n")
      trait <- trait[-wh]
      X <- X[-wh,]
    }
    if(r[1]==0 & r[2]==1) {
      trait <- trait+1 # require 1,2 labels
    }
  } else {
    trait <- numeric(0)
  }
  res <- .C("write_beagle", X@.Data, as.character(a1), as.character(a2),
            as.integer(bp), as.integer(trait),
            as.character(gfile), as.character(mfile),
            as.integer(nrow(X)),
            as.integer(ncol(X)), as.integer(length(trait)),
            rownames(X),
            colnames(X), logical(1))
  error <- res[[13]]
  if (error == 1)
    stop("Couldn't open output file",gfile)
  return(c(nrow(X), ncol(X)))
}

