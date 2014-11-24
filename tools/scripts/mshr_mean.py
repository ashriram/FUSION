import sys 
def main():
    try:
        f = open('mshr.stat.out','r')
    except:
        print "Could not open mshr.stat.out"
        sys.exit(0)
    
    coreNum = None
    numer = 0.0
    denom = 0.0
    for line in f:
        line = line.strip()
        if "Core" in line:
            coreNum = int(line.split()[1])
        elif ":" in line:
            assert(coreNum is not None)
            arr = [float(l) for l in line.split(':')]
            if arr[0] == 0: continue
            # Weighted Harmonic Mean
            # numer += arr[1] 
            # denom += arr[1]/arr[0]
            # Weighted Arithmetic Mean
            numer += arr[0]*arr[1] 
            denom += arr[1] 
        else:
            print "Core ",coreNum,(numer/denom)
            numer = 0.0
            denom = 0.0

if __name__ == "__main__":
    main()
