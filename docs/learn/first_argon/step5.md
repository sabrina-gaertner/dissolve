---
title: Step 5 - Equilibrate the System
grand_parent: Learn Dissolve
parent: Liquid Argon
nav_order: 7
---
# Liquid Argon

## 5) Equilibrate the System

With two of our processing layers set up we can start to run the simulation and monitor how the system is evolving. There are several ways to run the simulation within the Dissolve GUI:

- Click the _Run_{: .text-green-100} button on the left-hand side of the main window.
- Use _Simulation→Run_{: .text-green-100} from the main menu.
- Press `Ctrl-R`.

Do one of those to set the simulation running. Note the counter in the top-left of the main window which tracks the current iteration.

While the simulation is running you cannot edit any input values, keywords etc., but you can investigate the simulation's progress and output as it happens. For example, you could go to your _Standard Atomic (MC/MD)_ evolution layer and double-click the [`Energy`](/modules/energy) module to see a plot of the total energy of the configuration.

If you have the [`NeutronSQ`](/modules/neutronsq) module tab still open (if you don't, go back to your _RDF and Neutron S(Q)_ tab and double-click on the [`NeutronSQ`](/modules/neutronsq) module) you can see how the calculated structure factor and total G(r) compare to the experimental data we loaded in. After the simulation has been running for a little while (perhaps 100 iterations), you'll see that the simulation and experiment actually compare quite favourably, with the G(r) and F(Q) looking something like this:

![Equilibrated total G(r) for liquid argon](equilibrated-gr.png){: .img-centre}
![Equilibrated total F(Q) for liquid argon](equilibrated-fq.png){: .img-centre}

We'll now stop the simulation by doing one of:

- Click the _Pause_{: .text-green-100} button on the left-hand side of the main window.
- Use _Simulation→Pause_{: .text-green-100} from the main menu.
- Press `Esc`.

Now it's time to think about refining the pair potential to see if we can get better agreement with the experimental data in the next step.

[Previous Step](step4b.md){: .btn }   [Next Step](step6.md){: .btn .right}