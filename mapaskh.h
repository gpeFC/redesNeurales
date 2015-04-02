	// Declaracion clase Neurona.
class Neurona{
	private:
		double* pesos;
	public:
		Neurona(int dim);
		void borrarPesos();
};
	// Implementacion clase Neurona.
Neurona::Neurona(int dim){
	double* pesos = new double[dim];
	for(int i=0; i<dim; i++)
		pesos[i] = 0.0;
}

	// Declaracion clase Mapa.
class Mapa{
	private:
		Neurona* mapa;
	public:
		Mapa();
};
	// Implementacion clase Mapa.
Mapa::Mapa(){
}