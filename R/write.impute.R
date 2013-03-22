write.impute <-
function(X,a1,a2,bp,pedfile,snp.id=NULL) {
  if (!is(X, "snp.matrix"))
    stop("argument must be a snp.matrix object")
  if(any(a1=="" | is.na(a1) | a2=="" | is.na(a2) | a1==a2))
    stop("alleles must be non-missing characters, and each pair must contain different bases")
  if(length(a1)!=ncol(X))
    stop("require ncol(X) == length(a1) == length(a2)")
  if(length(bp)!=ncol(X))
    stop("require ncol(X) == length(bp)")
  if(is.null(snp.id))
    snp.id <- sprintf("SNP%s",1:ncol(X))
  res <- .C("write_impute", X@.Data, as.character(a1), as.character(a2),
            as.integer(bp), as.character(pedfile), as.integer(nrow(X)),
            as.integer(ncol(X)), rownames(X),
            colnames(X), snp.id, logical(1))
  error <- res[[11]]
  if (error == 1)
    stop("Couldn't open output file",pedfile)
  return(c(nrow(X), ncol(X)))
}

