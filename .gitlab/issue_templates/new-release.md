<!--
This template is for tracking a release of ParaView. Please replace the
following strings with the associated values:

  - `@VERSION@` - replace with base version, e.g., 5.7.0
  - `@RC@` - for release candidates, replace with "-RC?". For final, replace with "".
  - `@MAJOR@` - replace with major version number
  - `@MINOR@` - replace with minor version number

Please remove this comment.
-->

# Preparatory steps

  - Update ParaView guides
    - User manual
      - [ ] Rename to ParaViewGuide-@VERSION@.pdf
      - [ ] Upload to www.paraview.org/files/v@MAJOR@.@MINOR@
    - Catalyst Guide
      - [ ] Rename to ParaViewCatalystGuide-@VERSION@.pdf
      - [ ] Upload to www.paraview.org/files/v@MAJOR@.@MINOR@
    - Getting Started Guide
      - [ ] Rename to ParaViewGettingStarted-@VERSION@.pdf
      - [ ] Upload to www.paraview.org/files/v@MAJOR@.@MINOR@
    - Assemble release notes into `Documentation/release/ParaView-@VERSION@`.
      - [ ] Get positive review and merge.

# Update ParaView

<!--
Keep the relevant items for the kind of release this is.

If making a first release candidate from master, i.e., `v@MAJOR@.@MINOR@.0-RC1`:

  - [ ] Update `master` branch for **paraview**
```
git fetch origin
git checkout master
git merge --ff-only origin/master
git submodule update --recursive --init
```
  - [ ] Update `version.txt` and tag the commit
```
git checkout -b update-to-v@VERSION@@RC@
echo @VERSION@@RC@ > version.txt
git commit -m 'Update version number to @VERSION@@RC@' version.txt
git tag -a -m 'ParaView @VERSION@@RC@' v@VERSION@@RC@ HEAD
```
  - Integrate changes to `master` branch
    - [ ] Create a merge request targeting `master` (do *not* add `Backport: release`)
    - [ ] Get positive review
    - [ ] `Do: merge`
  - Update VTK's `paraview/release` branch
    - [ ] Change directory to VTK source
    - [ ] `git push origin <paraview-vtk-submodule-hash>:paraview/release`
    - [ ] Update kwrobot with the new `paraview/release` branch rules
  - Integrate changes to `release` branch
    - [ ] Change directory to ParaView source. Stay on the `update-to-v@VERSION@@RC@` branch.
    - [ ] `git config -f .gitmodules submodule.VTK.branch paraview/release`
    - [ ] `git commit -m "release: follow VTK's paraview/release branch" .gitmodules`
    - [ ] Merge new `release` branch into `master` using `-s ours`
      - `git checkout master`
      - `git merge --no-ff -s ours -m "Merge branch 'release'" update-to-v@VERSION@@RC@`
    - [ ] `git push origin master update-to-v@VERSION@@RC@:release v@VERSION@@RC@`
    - [ ] Update kwrobot with the new `release` branch rules

If making a release from the `release` branch, e.g., `v@MAJOR@.@MINOR@.0-RC2 or above`:

  - [ ] Update `release` branch for **paraview**
```
git fetch origin
git checkout release
git merge --ff-only origin/release
git submodule update --recursive --init
```
  - [ ] Update `version.txt` and tag the commit
```
git checkout -b update-to-v@VERSION@@RC@
echo @VERSION@@RC@ > version.txt
git commit -m 'Update version number to @VERSION@@RC@' version.txt
git tag -a -m 'ParaView @VERSION@@RC@' v@VERSION@@RC@ HEAD
```
  - Integrate changes to `master` branch
    - [ ] Create a merge request targeting `master` (do *not* add `Backport: release`)
    - [ ] Get positive review
    - [ ] `Do: merge`
  - Integrate changes to `release` branch
    - [ ] `git push origin update-to-v@VERSION@@RC@:release v@VERSION@@RC@`

If making a non-RC release, additionally:

  - Update documentation page
    - [ ] See `https://github.com/Kitware/paraview-docs/blob/master/README.md`
-->

  - Create tarballs
    - [ ] ParaView (`Utilities/Maintenance/create_tarballs.bash --txz --tgz --zip -v v@VERSION@@RC@`)
  - Upload tarballs to `paraview.org`
    - [ ] `rsync -rptv $tarballs paraview.release:ParaView_Release/v@MAJOR@.@MINOR@/`

# Update ParaView-Superbuild

<!--
Keep the relevant items for the kind of release this is.

If making a first release candidate from master, i.e., `v@MAJOR@.@MINOR@.0-RC1`:

  - [ ] Update `master` branch for **paraview/paraview-superbuild**
```
git fetch origin
git checkout master
git merge --ff-only origin/master
git submodule update
git checkout -b update-to-v@VERSION@@RC@
```
  - Update `CMakeLists.txt`
    - [ ] `git checkout -b update-to-v@VERSION@@RC@`
    - [ ] Update PARAVIEW_VERSION_DEFAULT to the release version (without RC*)
    - [ ] Set ParaView source selections in `CMakeLists.txt` and force explicit
      version in `CMakeLists.txt`:
```
# Force source selection setting here.
set(paraview_SOURCE_SELECTION "@VERSION@@RC@" CACHE STRING "Force version to @VERSION@@RC@" FORCE)
set(paraview_FROM_SOURCE_DIR OFF CACHE BOOL "Force source dir off" FORCE)
```
  - Update versions
    - [ ] Guide selections in `versions.cmake`
    - [ ] `paraview_SOURCE_SELECTION` version in `README.md`
    - [ ] Docker: update default tag strings (in `Scripts/docker/ubuntu/Dockerfile`)
      - [ ] ARG PARAVIEW_TAG=v@VERSION@@RC@
      - [ ] ARG SUPERBUILD_TAG=v@VERSION@@RC@
    - [ ] Commit changes and push to GitLab
```
git add versions.cmake CMakeLists.txt Scripts/docker/ubuntu/Dockerfile
git commit -m "Update the default version to @VERSION@@RC@"
git gitlab-push
```
  - Integrate changes to `master` branch
    - [ ] Create a merge request targeting `master`, title beginning with WIP (do *not* add `Backport: release` to description)
    - [ ] Build binaries (`Do: test`)
    - [ ] Download the binaries that have been generated in the dashboard results. They will be deleted within 24 hours.
    - [ ] Remove explicit version forcing added in CMakeLists.txt and force push
```
git add CMakeLists.txt
git commit --amend
git gitlab-push -f
```
  - Finalize merge request
    - [ ] Remove WIP from merge request title
    - [ ] Get positive review
    - [ ] `Do: merge`
    - [ ] `git tag -a -m 'ParaView superbuild @VERSION@@RC@' v@VERSION@@RC@ HEAD`
  - Update common-superbuild's `paraview/release` branch
    - [ ] Change directory to superbuild source
    - [ ] `git push origin <paraview-superbuild-submodule-hash>:paraview/release`
    - [ ] Update kwrobot with the new `paraview/release` branch rules
  - Integrate changes to `release` branch
    - [ ] Change directory to ParaView Superbuild source. Stay on the `update-to-v@VERSION@@RC@` branch.
    - [ ] `git config -f .gitmodules submodule.superbuild.branch paraview/release`
    - [ ] `git commit -m "release: follow common-superbuild's paraview/release branch" .gitmodules`
    - [ ] Merge new `release` branch into `master` using `-s ours`
      - `git checkout master`
      - `git merge --no-ff -s ours -m "Merge branch 'release'" update-to-v@VERSION@@RC@`
    - [ ] `git push origin update-to-v@VERSION@@RC@:release v@VERSION@@RC@`
    - [ ] Update kwrobot with the new `release` branch rules

If making a release from the `release` branch, e.g., `v@MAJOR@.@MINOR@.0-RC2 or above`:

  - [ ] Update `release` branch for **paraview/paraview-superbuild**
```
git fetch origin
git checkout release
git merge --ff-only origin/release
git submodule update
git checkout -b update-to-v@VERSION@@RC@
```
  - Update `CMakeLists.txt`
    - [ ] Set ParaView source selections in `CMakeLists.txt` and force explicit
      version in `CMakeLists.txt`:
```
# Force source selection setting here.
set(paraview_SOURCE_SELECTION "@VERSION@@RC@" CACHE STRING "Force version to @VERSION@@RC@" FORCE)
set(paraview_FROM_SOURCE_DIR OFF CACHE BOOL "Force source dir off" FORCE)
```
  - Update versions
    - [ ] Guide selections in `versions.cmake`
    - [ ] Docker: update default tag strings (in `Scripts/docker/ubuntu/Dockerfile`)
      - [ ] ARG PARAVIEW_TAG=v@VERSION@@RC@
      - [ ] ARG SUPERBUILD_TAG=v@VERSION@@RC@
    - [ ] Commit changes and push to GitLab
```
git add versions.cmake CMakeLists.txt Scripts/docker/ubuntu/Dockerfile
git commit -m "Update the default version to @VERSION@@RC@"
git gitlab-push
```
  - Integrate changes to `master` branch
    - [ ] Create a merge request targeting `master`, title beginning with WIP (do *not* add `Backport: release` to description)
    - [ ] Build binaries (`Do: test`)
    - [ ] Download the binaries that have been generated in the dashboard results. They will be deleted within 24 hours.
    - [ ] Remove explicit version forcing added in CMakeLists.txt, amend the commit, and force push
```
git add CMakeLists.txt
git commit --amend
git gitlab-push -f
```
  - Finalize merge request
    - [ ] Remove WIP from merge request title
    - [ ] Get positive review
    - [ ] `Do: merge`
    - [ ] `git tag -a -m 'ParaView superbuild @VERSION@@RC@' v@VERSION@@RC@ HEAD`
  - Integrate changes to `release` branch
    - [ ] `git push origin update-to-v@VERSION@@RC@:release v@VERSION@@RC@`
-->

# Sign macOS binaries

  - [ ] Upload to signing server, run script, download resulting .pkg and .dmg files
  - [ ] Install from .pkg and verify that it is signed with `codesign -dvvv /Applications/ParaView-@VERSION@@RC@.app/`
  - [ ] Install from .dmg and verify that it is signed with `codesign -dvvv /Applications/ParaView-@VERSION@@RC@.app/`

# Validating binaries

  - For each binary, check
    - [ ] Getting started guide opens
    - [ ] Examples load and match thumbnails in dialog
    - [ ] Python
    - [ ] `import numpy`
    - [ ] Plugins are present and load properly
    - [ ] Text source LaTeX `$A^2$`
    - [ ] OSPRay raycasting and pathtracing runs
    - [ ] OptiX pathtracing runs
    - [ ] IndeX runs
    - [ ] AutoMPI

  - Binary checklist
    - [ ] macOS
    - [ ] Linux
    - [ ] Linux osmesa
    - [ ] Windows MPI (.exe)
    - [ ] Windows MPI (.zip)
    - [ ] Windows no-MPI (.exe)
    - [ ] Windows no-MPI (.zip)

# Upload binaries

  - [ ] Upload binaries to `paraview.org` (`rsync -rptv $binaries paraview.release:ParaView_Release/v@MAJOR@.@MINOR@/`)
  - [ ] Ask @utkarsh.ayachit to regenerate `https://www.paraview.org/files/listing.txt` and `md5sum.txt` on the website

```
buildListing.sh
updateMD5sum.sh v@MAJOR@.@MINOR@
```

  - [ ] Test download links on https://www.paraview.org/download

<!--
If making a non-RC release:

# Update documentation

  - [ ] Upload versioned documentation to `https://github.com/kitware/paraview-docs`
  - [ ] Write and publish blog post with release notes.
  - [ ] Update release notes
    (https://www.paraview.org/Wiki/ParaView_Release_Notes)
-->

# Post-release

  - [ ] Post an announcement in the Announcements category on
        [discourse.paraview.org](https://discourse.paraview.org/).
<!--
If making a non-RC release:

  - [ ] Update link to ParaView Guide PDF at https://www.paraview.org/paraview-guide/
  - [ ] Move unclosed issues to next release milestone in GitLab
-->

/cc @ben.boeckel
/cc @cory.quammen
/cc @utkarsh.ayachit
/label ~"priority:required"
