from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from flask import Flask, request, jsonify

"""Serwer API obslugujacy baze"""
app = Flask(__name__)
Base = declarative_base()

"""Klasy z poprzedniego zadania"""
class Osoba(Base):
    __tablename__ = "osoby"
    id = Column(Integer, primary_key=True)
    imie = Column(String, nullable=False)
    email = Column(String, nullable=False, unique=True)
    pozyczone = relationship("Ksiazka", back_populates="wlasciciel")


class Ksiazka(Base):
    __tablename__ = "ksiazki"
    id = Column(Integer, primary_key=True)
    tytul = Column(String, nullable=False)
    autor = Column(String, nullable=False)
    rok = Column(Integer, nullable=False)
    kto_pozyczyl = Column(Integer, ForeignKey("osoby.id"))
    wlasciciel = relationship("Osoba", back_populates="pozyczone")


engine = create_engine('sqlite:///baza_danych.db')
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
session = Session()

"""Zadania dla serwera"""
@app.route("/ksiazki", methods=["GET"])
def get_ksiazki():
    ksiazki = session.query(Ksiazka).all()
    ksiazki_json = [{"id": ksiazka.id,
                     "tytul": ksiazka.tytul,
                     "autor": ksiazka.autor,
                     "rok": ksiazka.rok} for ksiazka in ksiazki]
    return jsonify(ksiazki_json)


@app.route("/ksiazki/<int:ksiazka_id>", methods=["GET"])
def get_ksiazka(ksiazka_id):
    ksiazka = session.query(Ksiazka).filter_by(id=ksiazka_id).first()
    if (ksiazka):
        ksiazka_json = {
            "id": ksiazka.id,
            "tytul": ksiazka.tytul,
            "autor": ksiazka.autor,
            "rok": ksiazka.rok}
        return jsonify(ksiazka_json)
    else:
        return jsonify({"message": "Nie znaleziono"}), 404


@app.route("/ksiazki", methods=["POST"])
def add_ksiazka():
    data = request.json
    nowa = Ksiazka(tytul=data["tytul"], autor=data["autor"], rok=data["rok"])
    session.add(nowa)
    session.commit()
    return jsonify({"message": "Dodano"}), 201


@app.route("/ksiazki/<int:ksiazka_id>", methods=["PUT"])
def update_ksiazka(ksiazka_id):
    data = request.json
    ksiazka = session.query(Ksiazka).filter_by(id=ksiazka_id).first()
    if ksiazka:
        ksiazka.tytul = data["tytul"]
        ksiazka.autor = data["autor"]
        ksiazka.rok = data["rok"]
        session.commit()
        return jsonify({"message": "Zaaktualizowano"}), 200
    else:
        return jsonify({"message": "Nie znaleziono"}), 404


@app.route("/ksiazki/<int:ksiazka_id>", methods=["DELETE"])
def delete_ksiazka(ksiazka_id):
    ksiazka = session.query(Ksiazka).filter_by(id=ksiazka_id).first()
    if ksiazka:
        session.delete(ksiazka)
        session.commit()
        return jsonify({"message": "Usunieto"}), 200
    else:
        return jsonify({"message": "Nie znaleziono"}), 404


if __name__ == "__main__":
    app.run(debug=True)
