import MTools

x = MTools.create_matrix(1,1)
x = MTools.add_matrix(x, x)
MTools.print_matrix(x)
MTools.free_matrix(x)