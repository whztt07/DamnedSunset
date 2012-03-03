/**
 * 
 */
package mapeditor.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import mapeditor.controler.System;
import mapeditor.util.CellType;
import mapeditor.util.ControllerListener;
import mapeditor.util.ElementType;
import mapeditor.util.EntityType;
import mapeditor.util.Position;

/**
 * @author Guibrush
 *
 */
public class PalettePanel extends JPanel implements ControllerListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JLabel _labelEntities, _labelCells, _labelEmpty, _labelElementSelected;
	private JPanel _panelElements, _panelEntities, _panelCells, _panelElementSelected, _panelColorElementSelected;
	
	private Vector<TypeButtonGroup> _cellTypes;
	private Vector<TypeButtonGroup> _entityTypes;
	
	private System _system;
	
	public PalettePanel(System system) {
		
		super();
		
		_system = system;
		
		_cellTypes =  new Vector<TypeButtonGroup>();
		_entityTypes =  new Vector<TypeButtonGroup>();
		
		setLayout(new BorderLayout());
		
		_panelElements = new JPanel();
		_panelElements.setLayout(new GridLayout(0, 1));
		add(_panelElements, BorderLayout.NORTH);
		
		_panelCells = new JPanel();
		_panelCells.setLayout(new GridLayout(0, 2));
		_panelElements.add(_panelCells);
		
		_labelCells = new JLabel("Celdas:");
		_panelCells.add(_labelCells);
		
		_labelEmpty = new JLabel(" ");
		_panelCells.add(_labelEmpty);
		
		_panelEntities = new JPanel();
		_panelEntities.setLayout(new GridLayout(0, 2));
		_panelElements.add(_panelEntities);
		
		_labelEntities = new JLabel("Entidades:");
		_panelEntities.add(_labelEntities);
		
		_labelEmpty = new JLabel(" ");
		_panelEntities.add(_labelEmpty);
		
		_panelElementSelected = new JPanel();
		add(_panelElementSelected, BorderLayout.SOUTH);
		
		_labelElementSelected = new JLabel();
		_panelElementSelected.add(_labelElementSelected);
		
		_panelColorElementSelected = new JPanel();
		_panelElementSelected.add(_panelColorElementSelected);
		
	}
	
	protected void paintComponent(Graphics g) {
		
		super.paintComponent(g);
		
		JButton button;
		
		if (_cellTypes != null)
			for (TypeButtonGroup cellTypeButton : _cellTypes) {
				
				if (cellTypeButton.getButton() == null) {
					
					/*_labelCells = new JLabel(cellTypeButton.getType().getType());
					_panelCells.add(_labelCells);*/
					
					button = new JButton(cellTypeButton.getType().getType());
					button.setBackground(_system.getPreferencesColorTypeCell((CellType) cellTypeButton.getType()));
					button.addActionListener(new ButtonPalette(cellTypeButton.getType()));
					_panelCells.add(button);
					
					cellTypeButton.setButton(button);
					
				}
				
			}
		
		if (_entityTypes != null)
			for (TypeButtonGroup entityTypeButton : _entityTypes) {
				
				if (entityTypeButton.getButton() == null) {
					
					/*_labelEntities = new JLabel(entityTypeButton.getType().getType());
					_panelEntities.add(_labelEntities);*/
					
					button = new JButton(entityTypeButton.getType().getType());
					button.setBackground(_system.getPreferencesColorTypeEntity((EntityType) entityTypeButton.getType()));
					button.addActionListener(new ButtonPalette(entityTypeButton.getType()));
					_panelEntities.add(button);
					
					entityTypeButton.setButton(button);
					
				}
				
			}
		
	}
	
	private void refreshFromPreferences() {
		
		Vector<CellType> cellTypesTemp = _system.getPreferencesCellTypes();
		
		TypeButtonGroup tmp;
		
		for (CellType cellType : cellTypesTemp) {
			
			tmp = new TypeButtonGroup(cellType, null);
			
			if (!_cellTypes.contains(tmp))
				_cellTypes.add(tmp);
			
		}
		
		Vector<EntityType> entityTypesTemp = _system.getPreferencesEntityTypes();
		
		for (EntityType entityType : entityTypesTemp) {
			
			tmp = new TypeButtonGroup(entityType, null);
			
			if (!_entityTypes.contains(tmp))
				_entityTypes.add(tmp);
			
		}
		
		repaint();
		
	}
	
	public void repaint() {
		
		super.repaint();
		
		Container parent = getParent();
		
		if (parent != null)
			parent.repaint();
		
	}
	
	public void initialize() {
		
		refreshFromPreferences();
		
	}

	@Override
	public void cellSelected(Position cell) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void cellDeSelected() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void cellChanged(Position cell, CellType cellType) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void newMap(int width, int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showCellType(String cellType) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showEntityMessage(String message) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showEntityParameter(String name, String value) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void preferencesChanged() {
		
		refreshFromPreferences();
		
	}
	
	@Override
	public void typeElementSelected(ElementType elementType, int height, int width) {
		
		_labelElementSelected.setText(elementType.getType() + " " + Integer.toString(height) + "X" + Integer.toString(width));
		
		Color color;
		
		if (elementType instanceof CellType)
			color = _cellTypes.get(_cellTypes.indexOf(new TypeButtonGroup(elementType, null))).getButton().getBackground();
		else
			color = _entityTypes.get(_entityTypes.indexOf(new TypeButtonGroup(elementType, null))).getButton().getBackground();
		
		_panelColorElementSelected.setBackground(color);
		
	}
	
	@Override
	public void typeElementDeSelected() {
		
		_labelElementSelected.setText(" ");
		
		_panelColorElementSelected.setBackground(_panelElementSelected.getBackground());
		
	}
	
	@Override
	public void newEntity(Position[] posList, EntityType entityType) {
		// TODO Auto-generated method stub
		
	}
	
	@Override
	public void removeEntity(Position[] posList) {
		// TODO Auto-generated method stub
		
	}
	
	class ButtonPalette implements ActionListener {

		private ElementType _type;
		
		public ButtonPalette(ElementType type) {
			
			_type = type;
			
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			
			_system.clicked(_type);
			
		}
		
	}

}