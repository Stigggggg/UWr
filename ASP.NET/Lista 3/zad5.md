Items, bo obiekty takie jak SqlConnection lub DataContext powinny być tworzone i wykorzystywane tylko na czas pojedynczego żądania, a następnie zwalniane. 

Application - ten sam obiekt byłby współdzielony przez równoczesne żądania, ryzyko wyścigu i trudności w zarządzaniu.

Session - ten sam obiekt przypisany do całej sesji, zagrożenie wycieków pamięci, bo DataContext nie byłby zwalniany po zakończeniu.