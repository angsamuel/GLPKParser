from pymprog import *  # Import the module
# index and data
xid, rid = range(3), range(3)
c = (10.0, 6.0, 4.0)
mat = [ (1.0, 1.0, 1.0),     
        (10.0, 4.0, 5.0),   
        (2.0, 2.0, 6.0)]   
b = (100.0, 600.0, 300.0)
#problem definition
beginModel('basic')  
verbose(True)
x = var(xid, 'X') #create variables
maximize( #set objective
  sum(c[i]*x[i] for i in xid), 'myobj'
)
r=st( #set constraints
  sum(x[j]*mat[i][j] for j in xid) <= b[i] for i in rid
)
solve() #solve and report
print "Solver status:", status()
print 'Z = %g;' % vobj()  # print obj value
#Print variable names and primal values
print ';\n'.join('%s = %g {dual: %g}' % (
   x[i].name, x[i].primal, x[i].dual) 
                    for i in xid)
print ';\n'.join('%s = %g {dual: %g}' % (
   r[i].name, r[i].primal, r[i].dual) 
                    for i in rid)

# Since version 0.3.0
print reportKKT()
print "Environment:", env
for pn in dir(env):
    if pn[:2]=='__'==pn[-2:]: continue
    print pn, getattr(env, pn)
# Since version 0.4.2
print evaluate(sum(x[i]*(i+x[i])**2 for i in xid))
print sum(x[i].primal*(i+x[i].primal)**2 for i in xid)
endModel() #Good habit: do away with the problem
