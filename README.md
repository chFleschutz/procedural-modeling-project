# Procedural Modeling Project

This repo contains a project from the lecture Procedural Modelling.
It features a scene build with procedural modelling techniques in the [Vektoria Game Engine](https://www.hs-kempten.de/fakultaet-informatik/zentrale-einrichtungen/computerspiel-zentrum-games/vektoria)

The scene is a surreal landscape on a different planet, featuring snowy mountains peaking out of a quiet, blood-red sea. 
In the middle of the environment stands a small hill, crowned by a round gallery. 
The hill is surrounded by a diamond-shaped road that leads to nowhere, adding a sense of mystery.
At the heart of the gallery lies the C.U.B.E. (**C**rucial **U**niversal **B**ase **E**ntity), which is currently being abducted by a blue beam emitted from a spinning alien spaceship hovering above. 

The contrast between the terrestrial mountain terrain with the old gallery structure and the unfamiliar red sea and the alien space ship creates a compelling and mysterious scene.


## Project Requierements

- **Special Object:**

    Alien spaceship with spinning orbs abducting the C.U.B.E.

- **Terrain:**

    Snowy Mountains peaking through a blood red sea

- **Infrastructure:**

    Diamond shaped road on top of a hill

- **Building:**

    Rounded gallery with oval arch doors guarding the C.U.B.E.
  
- **Textures:**

    Brushed metal material with albedo, specular, bump and height textures generated procedurally in blender and baked into seamless textures



## Getting Started

1. Clone the repo
```bash
git clone https://github.com/chFleschutz/procedural-modeling-project.git
```

1. Download [Vektoria V23.13](https://syncandshare.lrz.de/getlink/fi47DdpSth1JFJYgWrUyUbpe/) (latest might also work)

1. Place the downloaded `lib` folder in the root directory of the repo (indicated by the file [PUT_VEKTORIA_LIB_HERE](PUT_VEKTORIA_LIB_HERE.txt))

1. Open the [solution](App/VektoriaApp.sln) in Visual Studio

1. Retarget the solution (Project -> Retarget Solution -> Ok)

1. Build and run
