write.simple <-
function(X,a1,a2,file,fsep="\t",gsep="",write.sampleid=TRUE) {
  if (!is(X, "snp.matrix"))
    stop("argument must be a snp.matrix object")
  if(any(a1=="" | is.na(a1) | a2=="" | is.na(a2) | a1==a2))
    stop("alleles must be non-missing characters, and each pair must contain different bases")  
  if(length(a1)!=ncol(X) | length(a1)!=length(a2))
    stop("require ncol(X) == length(a1) == length(a2)")
  if(nchar(fsep)>1 || nchar(gsep)>1)
    stop("fsep and gsep must be \"\" or single character strings\n")
  unlink(file)
  if(write.sampleid)
    cat("sampleid",fsep,sep="",file=file)
  cat(colnames(X),file=file,sep=fsep,append=TRUE)
  cat("\n",file=file,append=TRUE)
  res <- .C("write_prettybase", X@.Data,
            as.character(a1), as.character(a2),as.character(fsep),as.character(gsep),
            as.character(file), as.integer(nrow(X)),
            as.integer(ncol(X)), rownames(X),
            colnames(X), logical(1))
  error <- res[[11]]
  if (error == 1)
    stop("Couldn't write to file",file)
  return(c(nrow(X), ncol(X)))
}

