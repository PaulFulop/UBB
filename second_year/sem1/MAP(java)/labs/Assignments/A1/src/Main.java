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
//    var repo = new MemoryRepository();
//    AddEntities(repo);
//    var controller = new Controller(repo);
//
//
//    var view = new View(controller);
//    view.StartMenu();

    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    int sum = numbers.stream()
            .filter(e -> e % 5 == 0 || e % 2 == 0)
            .map(e -> {if (e % 5 == 0) return "AAAAA"; else return "BBB";})
            .map(e -> e.length())
            .reduce(0, Integer::sum);
    IO.println(sum);
}

private static void AddEntities(MemoryRepository repo) {
    repo.Add(new Flour(25, "faina_chinteni"));
    repo.Add(new Flour(15, "faina_bistrita"));
    repo.Add(new Sugar(60, "zahar_chinteni"));
    repo.Add(new Salt(80, "sare_chinteni"));
    repo.Add(new Sugar(10, "sare_pura"));
    repo.Add(new Flour(5, "best_flour"));
}