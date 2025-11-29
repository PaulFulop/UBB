/*
    2. Intr-un depozit de alimente exista sare,
    zahar si faina. Sa se afiseze produsele
    cu pretul mai mare decat 20Ron/kg.
 */

import controller.Controller;
import model.Flour;
import model.Sugar;
import model.Salt;
import repos.MemoryRepository;
import view.View;

void main() {
    var repo = new MemoryRepository();
    AddEntities(repo);
    var controller = new Controller(repo);


    var view = new View(controller);
    view.StartMenu();
}

private static void AddEntities(MemoryRepository repo) {
    repo.Add(new Flour(25, "faina_chinteni"));
    repo.Add(new Flour(15, "faina_bistrita"));
    repo.Add(new Sugar(60, "zahar_chinteni"));
    repo.Add(new Salt(80, "sare_chinteni"));
    repo.Add(new Sugar(10, "sare_pura"));
    repo.Add(new Flour(5, "best_flour"));
}