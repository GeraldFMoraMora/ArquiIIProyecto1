import re
import matplotlib.pyplot as plt

def convertir_a_float(texto):
    # Utiliza una expresión regular para extraer los dígitos y el punto decimal
    import re
    numero = re.sub(r'[^0-9.]', '', texto)
    return float(numero)

def getmSST():
    # Abre el archivo de texto en modo lectura
    with open('mSSTCC_results.txt', 'r') as archivo:
        lineas = archivo.readlines()

    # Inicializa diccionarios para almacenar los valores
    valores_I = {}
    valores_D = {}
    valores_LL = {}
        # Busca las líneas relevantes y almacena los valores en los diccionarios
    for linea in lineas:
        if 'I   refs:' in linea:
            valores_I['I   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  misses:' in linea:
            valores_I['I1  misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLi misses:' in linea:
            valores_I['LLi misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  miss rate:' in linea:
            valores_I['I1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLi miss rate:' in linea:
            valores_I['LLi miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'D   refs:' in linea:
            valores_D['D   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1 misses:' in linea:
            valores_D['D1 misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLd misses:' in linea:
            valores_D['LLd misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1  miss rate:' in linea:
            valores_D['D1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLd miss rate:' in linea:
            valores_D['LLd miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LL refs:' in linea:
            valores_LL['LL refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL misses:' in linea:
            valores_LL['LL misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL miss rate:' in linea:
            valores_LL['LL miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'

    return [valores_I,valores_D,valores_LL]

def getmSFS():
    # Abre el archivo de texto en modo lectura
    with open('mSFSCC_results.txt', 'r') as archivo:
        lineas = archivo.readlines()

    # Inicializa diccionarios para almacenar los valores
    valores_I = {}
    valores_D = {}
    valores_LL = {}
        # Busca las líneas relevantes y almacena los valores en los diccionarios
    for linea in lineas:
        if 'I   refs:' in linea:
            valores_I['I   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  misses:' in linea:
            valores_I['I1  misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLi misses:' in linea:
            valores_I['LLi misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  miss rate:' in linea:
            valores_I['I1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLi miss rate:' in linea:
            valores_I['LLi miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'D   refs:' in linea:
            valores_D['D   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1 misses:' in linea:
            valores_D['D1 misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLd misses:' in linea:
            valores_D['LLd misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1  miss rate:' in linea:
            valores_D['D1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLd miss rate:' in linea:
            valores_D['LLd miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LL refs:' in linea:
            valores_LL['LL refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL misses:' in linea:
            valores_LL['LL misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL miss rate:' in linea:
            valores_LL['LL miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'

    return [valores_I,valores_D,valores_LL]

def getmSNFS1():
    # Abre el archivo de texto en modo lectura
    with open('mSNFS1CC_results.txt', 'r') as archivo:
        lineas = archivo.readlines()

    # Inicializa diccionarios para almacenar los valores
    valores_I = {}
    valores_D = {}
    valores_LL = {}
        # Busca las líneas relevantes y almacena los valores en los diccionarios
    for linea in lineas:
        if 'I   refs:' in linea:
            valores_I['I   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  misses:' in linea:
            valores_I['I1  misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLi misses:' in linea:
            valores_I['LLi misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  miss rate:' in linea:
            valores_I['I1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLi miss rate:' in linea:
            valores_I['LLi miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'D   refs:' in linea:
            valores_D['D   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1 misses:' in linea:
            valores_D['D1 misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLd misses:' in linea:
            valores_D['LLd misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1  miss rate:' in linea:
            valores_D['D1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLd miss rate:' in linea:
            valores_D['LLd miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LL refs:' in linea:
            valores_LL['LL refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL misses:' in linea:
            valores_LL['LL misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL miss rate:' in linea:
            valores_LL['LL miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'

    return [valores_I,valores_D,valores_LL]

def getmSNFS2():
    with open('mSNFS2CC_results.txt', 'r') as archivo:
        lineas = archivo.readlines()

    valores_I = {}
    valores_D = {}
    valores_LL = {}
    for linea in lineas:
        if 'I   refs:' in linea:
            valores_I['I   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  misses:' in linea:
            valores_I['I1  misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLi misses:' in linea:
            valores_I['LLi misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'I1  miss rate:' in linea:
            valores_I['I1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLi miss rate:' in linea:
            valores_I['LLi miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'D   refs:' in linea:
            valores_D['D   refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1 misses:' in linea:
            valores_D['D1 misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LLd misses:' in linea:
            valores_D['LLd misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'D1  miss rate:' in linea:
            valores_D['D1  miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LLd miss rate:' in linea:
            valores_D['LLd miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
        elif 'LL refs:' in linea:
            valores_LL['LL refs'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL misses:' in linea:
            valores_LL['LL misses'] = convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip())
        elif 'LL miss rate:' in linea:
            valores_LL['LL miss rate'] = str(convertir_a_float(linea.split(':')[1].strip().split('(')[0].strip()))+'%'
    return [valores_I,valores_D,valores_LL]
 
def performanceViewer():
    valoresmSST = getmSST()
    valoresmSFS = getmSFS()
    valoresmSNFS1 = getmSNFS1()
    valoresmSNFS2 = getmSNFS2()
    valoresmSSTI = valoresmSST[0]
    valoresmSFSI = valoresmSFS[0]
    valoresmSNFS1I = valoresmSNFS1[0]
    valoresmSNFS2I = valoresmSNFS2[0]
    valoresmSSTD = valoresmSST[1]
    valoresmSFSD = valoresmSFS[1]
    valoresmSNFS1D = valoresmSNFS1[1]
    valoresmSNFS2D = valoresmSNFS2[1]
    valoresmSSTLL = valoresmSST[2]
    valoresmSFSLL = valoresmSFS[2]
    valoresmSNFS1LL = valoresmSNFS1[2]
    valoresmSNFS2LL = valoresmSNFS2[2]
    fig, ax = plt.subplots(3, 4)  
    fig.canvas.set_window_title("Performance Viewer")
    fig.suptitle("Case C")

    ax[0,0].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTI["I   refs"], valoresmSFSI["I   refs"], valoresmSNFS1I["I   refs"],valoresmSNFS2I["I   refs"]], color="#00FF00")
    ax[0,0].set_title("REFERENCIAS A INSTRUCCIONES")
    
    ax[0,1].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTI["I1  misses"], valoresmSFSI["I1  misses"], valoresmSNFS1I["I1  misses"],valoresmSNFS2I["I1  misses"]], color="#00FF00")
    ax[0,1].set_title("FALLOS EN CACHE DE NIVEL 1 INST")
    
    ax[0,2].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTI["LLi misses"], valoresmSFSI["LLi misses"], valoresmSNFS1I["LLi misses"],valoresmSNFS2I["LLi misses"]], color="#00FF00")
    ax[0,2].set_title("FALLOS EN CACHE DE ULTIMO NIVEL INST")
    
    ax[0,3].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTI["I1  miss rate"], valoresmSFSI["I1  miss rate"], valoresmSNFS1I["I1  miss rate"],valoresmSNFS2I["I1  miss rate"]], color="#00FF00")
    ax[0,3].set_title("TAZA FALLOS NIVEL 1 INST")
    
    ax[1,0].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTI["LLi miss rate"], valoresmSFSI["LLi miss rate"], valoresmSNFS1I["LLi miss rate"],valoresmSNFS2I["LLi miss rate"]], color="#00FF00")
    ax[1,0].set_title("TAZA DE FALLOS ULTIMO NIVEL INST")
    
    ax[1,1].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTD["D   refs"], valoresmSFSD["D   refs"], valoresmSNFS1D["D   refs"],valoresmSNFS2D["D   refs"]], color="#00FF00")
    ax[1,1].set_title("REFERENCIAS A DATOS")
    
    ax[1,2].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTD["D1  miss rate"], valoresmSFSD["D1  miss rate"], valoresmSNFS1D["D1  miss rate"],valoresmSNFS2D["D1  miss rate"]], color="#00FF00")
    ax[1,2].set_title("TAZA FALLOS NIVEL 1 DATOS")
    
    ax[1,3].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTD["LLd miss rate"], valoresmSFSD["LLd miss rate"], valoresmSNFS1D["LLd miss rate"],valoresmSNFS2D["LLd miss rate"]], color="#00FF00")
    ax[1,3].set_title("TAZA DE FALLOS ULTIMO NIVEL DATOS")
    
    ax[2,0].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTD["LLd misses"], valoresmSFSD["LLd misses"], valoresmSNFS1D["LLd misses"],valoresmSNFS2D["LLd misses"]], color="#00FF00")
    ax[2,0].set_title("FALLOS EN CACHE DE ULTIMO NIVEL DATOS")
    
    ax[2,1].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTLL["LL refs"], valoresmSFSLL["LL refs"], valoresmSNFS1LL["LL refs"],valoresmSNFS2LL["LL refs"]], color="#00FF00")
    ax[2,1].set_title("REFERENCIAS EN ULTIMO NIVEL INST & DATOS")
    
    ax[2,2].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTLL["LL misses"], valoresmSFSLL["LL misses"], valoresmSNFS1LL["LL misses"],valoresmSNFS2LL["LL misses"]], color="#00FF00")
    ax[2,2].set_title("FALLOS EN ULTIMO NIVEL INST & DATOS")
    
    ax[2,3].bar(["MSST", "MSFS", "MSNFS1", "MSNFS2"], [valoresmSSTLL["LL miss rate"], valoresmSFSLL["LL miss rate"], valoresmSNFS1LL["LL miss rate"],valoresmSNFS2LL["LL miss rate"]], color="#00FF00")
    ax[2,3].set_title("TAZA DE FALLOS EN ULTIMO NIVEL INST & DATOS")

    plt.tight_layout()  
    plt.show()
    
def main():   
    performanceViewer();
    
main()
