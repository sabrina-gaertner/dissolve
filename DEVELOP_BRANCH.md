# Develop Branch Worklist

## Prep
- Spatial density function calculation
- 2D plotting
- 3D plotting of surfaces (marching cubes)

## Main
- Add water example
- Add benzene example (inc. sdf/slicing comparison between equilibrated / refined simulations)
- Add silica example

## Other
- [General] Harmonise command-line arguments between CLI and GUI versions (use gengetopt?)

## More
- Importing CIF structures as Species - break up into molecular units? Need to provide basic information on the contained units, probably as empirical formula (e.g. for CuBTC would be 'Cu' and 'C9O6H3'). This info can then be used to find, rotate, and re-map those molecules in a unit cell (folded molecularly). The Species then contains a list of copies of that particular molecular unit, at real coordinates.  These can then be pasted into a supercell, replicating the crystal. Need to have options in the AddSpecies node to utilise symmetry copies. A species may also contain multiple variants of coordinates in the form of conformers (potentially weighted by some factor, e.g. deltaE??). Store both these in a list of copies_, storing coordinates only (we will always use the basic Species information as a template for elements, bonds etc., as well as forcefield terms.
