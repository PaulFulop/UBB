package com.example.model;
import jakarta.persistence.*;


@Entity
@Table(name = "SoftwareDeveloper")
public class SoftwareDeveloper {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private  String name;
    private  Integer age;
    private  String skills;

    public  Integer getId() {return id;}
    public void setId(Integer id) {this.id = id;}
    public String getName() {return name;}
    public void setName(String name) {this.name = name;}
    public Integer getAge() {return age;}
    public void setAge(Integer age) {this.age = age;}
    public String getSkills() {return skills;}
    public void setSkills(String skills) {this.skills = skills;}

}
