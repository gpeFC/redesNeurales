"""
Mapas AutoOrganizados.
"""

import random
from random import shuffle
from math import exp, sqrt

class Nodo(object):
	"""Nodo del mapa autoorganizado."""
	def __init__(self, dimension):
		super(Nodo, self).__init__()
		self.pesos = []
		for i in range(dimension):
			self.pesos.append(random.uniform(0.0,1.0))

	def ajustar_pesos(self, alpha, sigma, epsilon):
		"""
		Ajustar pesos sinapticos del nodo segun la regla de aprendizaje.
		"""
		for i in range(len(self.pesos)):
			self.pesos[i] += (alpha * sigma * epsilon)

class Mapa(object):
	"""Mapa autoorganizado."""
	def __init__(self, dimension, num_filas, num_columnas):
		super(Mapa, self).__init__()
		self.alpha = 0.0
		self.sigma = 0.0
		self.centros = []
		self.nodos = []
		for i in range(num_filas):
			vector = []
			for j in range(num_columnas):
				vector.append(Nodo(dimension))
			self.nodos.append(vector)

	def ajustar_alpha(self, epocas, epoca_actual, alpha_inicial, alpha_final):
		"""
		Ajustar el factor de aprendizaje para la epoca actual de 
		entrenamiento.
		"""
		self.alpha = alpha_inicial * ((alpha_final/alpha_inicial)**(epoca_actual/epocas))

	def ajustar_sigma(self, epocas, epoca_actual, sigma_inicial, sigma_final):
		"""
		Ajustar el radio de vecindad para la epoca actual de 
		entrenamiento.
		"""
		self.sigma = sigma_inicial * ((sigma_final/sigma_inicial)**(epoca_actual/epocas))

	def ajustar_nodos(self, dimension, vector_entrada, vector_neuronal):
		"""
		Ajustar el vector de pesos sinapticos de todos los nodos del 
		mapa para la epoca actual de entrenamiento.
		"""
		for nodos in self.nodos:
			for nodo in nodos:
				for i in range(dimension):
					nodo.pesos[i] += self.alpha * self.calcular_vecindad(
						self.sigma, vector_entrada, vector_neuronal) * (
						vector_entrada[i] - nodo.pesos[i])

	def calcular_distancia(self, vector_entrada, vector_neuronal):
		"""
		Calcula la distancia Euclidea entre un vector ingresado y el 
		vector de pesos sinapticos de un nodo del mapa.
		"""
		distancia = 0.0
		for i in range(len(vector_entrada)):
			distancia += (vector_entrada[i]-vector_neuronal[i])**2
		return sqrt(distancia)

	def calcular_vecindad(self, sigma, vector_vecino, vector_centro):
		"""
		Establece los nodos pertenecientes a una vecindad dada en torno
		a un centroide determinado.
		"""
		vecindad = 0.0
		for i in range(len(vector_vecino)):
			vecindad += (vector_vecino[i]-vector_centro[i])
		vecindad = vecindad**2
		return exp(-(vecindad/(2*sigma**2)))

	def ejecutar_mapeo(self, patron):
		"""
		Mapea un vector ingresado de acuerdo a las vecindades 
		establecidas durante el entrenamiento.
		"""
		similitud = 0.0
		centro = None
		for i in range(len(self.nodos)):
			for j in range(len(self.nodos[i])):
				if i==0 and j==0:
					similitud = self.calcular_distancia(patron, self.nodos[i][j].pesos)
					centro = self.nodos[i][j]
				else:
					distancia = self.calcular_distancia(patron, self.nodos[i][j].pesos)
					if distancia < similitud:
						similitud = distancia
						centro = self.nodos[i][j]
		return centro
					

	def entrenar_mapeo(self, epocas, dimension, patrones):
		"""
		Entrena el mapa para establecer vecindades de similidaridad
		de acuerdo a los patrones de entrenamiento.
		"""
		alpha_inicial, alpha_final = 0.0, 0.0
		while True:
			alpha_inicial, alpha_final = random.uniform(0.0,1.0), random.uniform(0.0,1.0)
			if alpha_final < alpha_inicial:
				break
		sigma_inicial, sigma_final = 0.0, 0.0
		while True:
			sigma_inicial, sigma_final = random.uniform(0.0,1.0), random.uniform(0.0,1.0)
			if sigma_final < sigma_inicial:
				break
		lista = range(len(patrones))
		for epoca in range(1,epocas+1):
			self.ajustar_alpha(epocas, epoca, alpha_inicial, alpha_final)
			self.ajustar_sigma(epocas, epoca, sigma_inicial, sigma_final)
			shuffle(lista)
			centros = []
			for indice in lista:
				similitud = 0.0
				centro = None
				for i in range(len(self.nodos)):
					for j in range(len(self.nodos[i])):
						if i==0 and j==0:
							similitud = self.calcular_distancia(patrones[indice],
								self.nodos[i][j].pesos)
							centro = self.nodos[i][j]
						else:
							distancia = self.calcular_distancia(patrones[indice],
								self.nodos[i][j].pesos)
							if distancia < similitud:
								similitud = distancia
								centro = self.nodos[i][j]
				self.ajustar_nodos(dimension, patrones[indice], centro.pesos)
				if len(centros) == 0:
					centros.append(centro)
				else:
					bandera = True
					for item in centros:
						if centro == item:
							bandera = False
							break
					if bandera:
						centros.append(centro)
			self.centros = centros


if __name__ == '__main__':
	patrones = []
	for i in range(50):
		patron = []
		patron.append(random.uniform(0.0,1.0))
		patron.append(random.uniform(0.0,1.0))
		patrones.append(patron)
	ejemplos = []
	for i in range(15):
		ejemplo = []
		ejemplo.append(random.uniform(0.0,1.0))
		ejemplo.append(random.uniform(0.0,1.0))
		ejemplos.append(ejemplo)

	mapa = Mapa(2,3,3)
	mapa.entrenar_mapeo(15,2,patrones)
	print "Hay %d centroides.\n" % len(mapa.centros)
	print "Nodos en el Mapa:"
	for nodos in mapa.nodos:
		for nodo in nodos:
			print nodo.pesos
	print
	print "Centroides:"
	for centro in mapa.centros:
		print centro.pesos

	mapeo = []
	for ejemplo in ejemplos:
		nodo = mapa.ejecutar_mapeo(ejemplo)
		if len(mapeo) == 0:
			mapeo.append(nodo)
		else:
			bandera = True
			for item in mapeo:
				if nodo == item:
					bandera = False
					break
			if bandera:
				mapeo.append(nodo)
	print
	print "Nodos mapeados:"
	for nodo in mapeo:
		print nodo.pesos
