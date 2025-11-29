BEGIN{
    sum=0
    
}

{
    sum += length($1)    
}

END{
    print sum
}
