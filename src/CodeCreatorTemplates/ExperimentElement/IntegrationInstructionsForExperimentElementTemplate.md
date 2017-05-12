# How to integrate the new Experiment Element: ExperimentElementTemplate
* add logic and gui part to CMakeLists.txt in the catalogue
```
add_subdirectory(ExperimentElementTemplate)
add_subdirectory(ExperimentElementTemplateGui)
```

* add instance of logic part in exps xml
```
<ExperimentElementInstance name="ExperimentElementTemplate" elementType="ExperimentElementTemplate" catalogue="CatalogName">
  <DeploymentParameter name="Standard_Instrument" value="ExperimentElementTemplate:1:ExperimentElementTemplate"/>
</ExperimentElementInstance>
```
* change DeploymentParameter to something valid, e.g. `Default:1:X`
* add window in expd file - experimentElementInstanceName should correspond to tag 'name' of node ExperimentElementInstance in exps file
```
<Window name="CatalogName_ExperimentElementTemplateWindow" caption="ExperimentElementTemplateWindow">
  <Layout spacing="7">
    <BoxSpecification/>
  </Layout>
  <Panel name="ExperimentElementTemplatePanelDescription" experimentElementInstanceName="ExperimentElementTemplate" panelType="ExperimentElementTemplatePanel"/>
</Window>
```
* add new window to a window group windowRef must be the name of the window
```
<WindowRef windowRef="CatalogName_ExperimentElementTemplateWindow"/> 
```